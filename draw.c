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


t_color	color_set(int  val_cl)
{
	t_color		cl;

	if (val_cl > 360)
	{
		val_cl = val_cl - 360;
	}
	if (val_cl >= 0 && val_cl < 121)
	{
		cl.b = 0;
		cl.g = val_cl * (255 / 120);
		cl.r = 255 - cl.g;
	}
	else if (val_cl < 240)
	{
		cl.b = (val_cl - 120) * 255 / 120;
		cl.g = 255 - cl.b;
		cl.r = 0;
	}
	else
	{
		cl.r = (val_cl - 240) * 255 /120;
		cl.g = 0;
		cl.b = 255 -cl.r;
	}
	return (cl);
}

//fy < 1 et > 0
void		draw_point(float fx, float fy, t_context * ctx_p, int z)
{
	int		i;
	int		xx;
	int		yy;

	float	x_max;


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


	t_color cl;

	cl = color_set(z * 10); //10 需要换成变量
	ctx_p->data_addr[i * 4 + 2] = cl.r;
	ctx_p->data_addr[i * 4 + 1] = cl.g;
	ctx_p->data_addr[i * 4 ] = cl.b;


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
 			if (fp1.y == fp.y)
 			{
 				z = 0;
 			}
 			else
 			{
 				z = z + 5;
 			}
 			draw_point(x, y, ctx_p, z);

 		}

 		else
 		{
 			x = fp.x;
 			y = fp.y + (((fp1.y - fp.y)*count)/(ctx_p->preci) );
 			z = 0;
 			draw_point(x, y, ctx_p, z);

 		}
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