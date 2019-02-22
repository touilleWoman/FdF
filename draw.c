/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:04:10 by jleblond          #+#    #+#             */
/*   Updated: 2019/02/22 13:04:11 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//fy < 1 et > 0
void	draw_point(float fx, float fy, char *data_addr)
{
	int		i;
	int		x;
	int		y;

	x = fx * WIN_Y;
	y = fy * WIN_Y;

	i = y*WIN_X + x;
	data_addr[2 + i * 4] = 0xff;
}

//point fp1 est apres fp
void	draw_trait(t_float_point  fp1, t_float_point  fp, char *data_addr, t_context *ctx_p)
{
	int		count;
	float	x;
	float	y;

	count = 0;
	while ( count <  (ctx_p->preci))
	{
		if ( fp1.x != fp.x)
		{
 			x = fp.x + (((fp1.x - fp.x)*count)/(ctx_p->preci) );
 			y = (((fp1.y - fp.y) / (fp1.x - fp.x)) * (x - fp.x)) + fp.y;
 		}
 		else
 		{
 			x = fp.x;
 			y = fp.y + (((fp1.y - fp.y)*count)/(ctx_p->preci) );
 		}
 		draw_point(x, y, data_addr);
 		count++;


	}
}



void	draw(t_map_params	mpp, char *data_addr, t_context *ctx_p)
{
	int		x;
	int		y;
	t_float_point  fp;
	//t_float_point  fp_max;

	t_float_point  fp1;
	t_float_point  fp2;


	x = 0;
	y = 0;
	while (y < mpp.y)
	{
		while (x < mpp.x)
		{
			fp = convert2d(x, y, mpp.map[y][x], mpp); //三者均为坐标值
			draw_point(fp.x, fp.y, data_addr);
///////////////draw line



			if (x == (mpp.x - 1) && y != (mpp.y - 1))
			{
				fp2 = convert2d(x , y + 1, mpp.map[y + 1][x], mpp); //point under  fp

				draw_trait(fp2, fp, data_addr, ctx_p);

			}
			if (y == (mpp.y - 1) && x != (mpp.x - 1))
			{
				fp1 = convert2d((x + 1), y, mpp.map[y][x + 1], mpp); //point on the right of fp

				draw_trait(fp1, fp, data_addr, ctx_p);
			}
			else if(x < (mpp.x - 1) && y < (mpp.y - 1))
			{
				fp1 = convert2d((x + 1), y, mpp.map[y][x + 1], mpp); //point on the right of fp
				fp2 = convert2d(x , y + 1, mpp.map[y + 1][x], mpp); //point under  fp

				draw_trait(fp1, fp, data_addr, ctx_p);
				draw_trait(fp2, fp, data_addr, ctx_p);
			}




////////////////////////draw line
			x++;
		}
		x = 0;
		y++;
	}



	//fp_max = convert2d(mpp.x - 1, mpp.y -1, mpp.map[mpp.y -1][mpp.x -1], mpp);
	//printf("xmax:%9.6fymax:%9.6f\n", fp_max.x, fp_max.y);


	// x = 0;
	// y = 2;
	// fp = convert2d(x, y, mpp.map[y][x], mpp);
	// y = y + 1;
	// fp2 = convert2d(x, y, mpp.map[y][x], mpp);

	// draw_trait(fp2, fp, data_addr);

}