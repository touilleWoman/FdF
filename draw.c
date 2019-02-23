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


// t_color	color_set(char  color_num)
// {


// 	// red = i * 4 + 2;
// 	// green = i * 4 + 1;
// 	// blue = i * 4;


// 	ctx_p->data_addr[i * 4 + 1] = z * 10;



// }

//fy < 1 et > 0
void		draw_point(float fx, float fy, t_context * ctx_p, int z)
{
	int		i;
	int		xx;
	int		yy;

	float	x_max;

	z =0;

	x_max = (ctx_p->mpp.x - 1.0) / (ctx_p->mpp.y -1);

	if ((fy > 1) || (fy < 0) || (fx < 0) || (fx > x_max))  //1.8转位变量
	{
		return ;
	}
	//printf("fx%9.6ffy%9.6f\n", fx, fy);
	xx = fx * WIN_Y;
	yy = fy * WIN_Y;
	if ((xx >= 1200) || (yy >= 900))
		return;
	i = yy * WIN_X + xx;
	ctx_p->data_addr[i * 4 + 2] = 0xff;


}

//point fp1 est apres fp
void	draw_trait(t_float_point  fp1, t_float_point  fp, t_context *ctx_p, int z)
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
 		draw_point(x, y, ctx_p, z);
 		count++;


	}
}



void	draw(t_context *ctx_p)
{
	int		x;
	int		y;
	t_float_point  fp;
	//t_float_point  fp_max;

	t_float_point  fp1;
	t_float_point  fp2;

	x = 0;
	y = 0;
	while (y < ctx_p->mpp.y)
	{
		while (x < ctx_p->mpp.x)
		{
			fp = convert2d(x, y, ctx_p->mpp.map[y][x], ctx_p); //三者均为坐标值

			draw_point(fp.x, fp.y, ctx_p, ctx_p->mpp.map[y][x]);
///////////////draw line



			if (x == (ctx_p->mpp.x - 1) && y != (ctx_p->mpp.y - 1))
			{
				fp2 = convert2d(x , y + 1, ctx_p->mpp.map[y + 1][x], ctx_p); //point under  fp

				draw_trait(fp2, fp, ctx_p, ctx_p->mpp.map[y][x]);

			}
			if (y == (ctx_p->mpp.y - 1) && x != (ctx_p->mpp.x - 1))
			{
				fp1 = convert2d((x + 1), y, ctx_p->mpp.map[y][x + 1], ctx_p); //point on the right of fp

				draw_trait(fp1, fp, ctx_p, ctx_p->mpp.map[y][x]);
			}
			else if(x < (ctx_p->mpp.x - 1) && y < (ctx_p->mpp.y - 1))
			{
				fp1 = convert2d((x + 1), y, ctx_p->mpp.map[y][x + 1], ctx_p); //point on the right of fp
				fp2 = convert2d(x , y + 1, ctx_p->mpp.map[y + 1][x], ctx_p); //point under  fp

				draw_trait(fp1, fp, ctx_p, ctx_p->mpp.map[y][x]);
				draw_trait(fp2, fp, ctx_p, ctx_p->mpp.map[y][x]);
			}

////////////////////////draw line

			x++;
		}
		x = 0;
		y++;
	}

	mlx_put_image_to_window(ctx_p->mlx_ptr, ctx_p->win_ptr, ctx_p->img_ptr, 10, 10);

}