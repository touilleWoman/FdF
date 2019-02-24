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

	if(val_cl < 0)
		val_cl = - val_cl;
	while (val_cl > 360)
		val_cl = val_cl - 360;

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
void		draw_point(float fx, float fy, t_context * ctx_p, float z)
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
	int		range;


	// if (z < 0) ???
	// {

	// }
	range = 120 * z / (ctx_p->mpp.z_max - ctx_p->mpp.z_min) + ctx_p->var_cl;

	cl = color_set(range);
	ctx_p->data_addr[i * 4 + 2] = cl.r;
	ctx_p->data_addr[i * 4 + 1] = cl.g;
	ctx_p->data_addr[i * 4 ] = cl.b;


}

//point fp1 est apres fp
void	draw_trait(t_float_point  fp1, t_float_point  fp, t_context *ctx_p, int z, int z1)
{
	int		count;
	float	x;
	float	y;
	float 	zz;

	count = 0;
	while ( count <  (ctx_p->preci))
	{
		if ( fp1.x != fp.x)
		{
 			x = fp.x + (((fp1.x - fp.x)*count)/(ctx_p->preci) );
 			y = (((fp1.y - fp.y) / (fp1.x - fp.x)) * (x - fp.x)) + fp.y;
 			if (fp1.y != fp.y)
 			{
 				zz = z + (z1- z) * count * 1.0 / ctx_p->preci;
 				//printf("zz: %9.6f\n", zz );
 			}
 			else
 			{
 				zz = z;
 			}
 			draw_point(x, y, ctx_p, zz);

 		}

 		else
 		{
 			x = fp.x;
 			y = fp.y + (((fp1.y - fp.y)*count)/(ctx_p->preci) );
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



	x = 0;
	y = 0;
	while (y < ctx_p->mpp.y)
	{
		while (x < ctx_p->mpp.x)
		{
			fp = convert2d(x, y, ctx_p->mpp.map[y][x], ctx_p); //三者均为坐标值

			draw_point(fp.x, fp.y, ctx_p, ctx_p->mpp.map[y][x]);
///////////////draw line
			t_float_point  fp1;
			t_float_point  fp2;


			if (x == (ctx_p->mpp.x - 1) && y != (ctx_p->mpp.y - 1))
			{
				fp2 = convert2d(x , y + 1, ctx_p->mpp.map[y + 1][x], ctx_p); //point under  fp

				draw_trait(fp2, fp, ctx_p, ctx_p->mpp.map[y][x],ctx_p->mpp.map[y + 1][x]);

			}
			if (y == (ctx_p->mpp.y - 1) && x != (ctx_p->mpp.x - 1))
			{
				fp1 = convert2d((x + 1), y, ctx_p->mpp.map[y][x + 1], ctx_p); //point on the right of fp

				draw_trait(fp1, fp, ctx_p, ctx_p->mpp.map[y][x],ctx_p->mpp.map[y][x + 1]);
			}
			else if(x < (ctx_p->mpp.x - 1) && y < (ctx_p->mpp.y - 1))
			{
				fp1 = convert2d((x + 1), y, ctx_p->mpp.map[y][x + 1], ctx_p); //point on the right of fp
				fp2 = convert2d(x , y + 1, ctx_p->mpp.map[y + 1][x], ctx_p); //point under  fp

				draw_trait(fp1, fp, ctx_p, ctx_p->mpp.map[y][x],ctx_p->mpp.map[y][x + 1]);
				draw_trait(fp2, fp, ctx_p, ctx_p->mpp.map[y][x],ctx_p->mpp.map[y + 1][x]);
			}

////////////////////////draw line

			x++;
		}
		x = 0;
		y++;
	}
	mlx_string_put(ctx_p->mlx_ptr, ctx_p->win_ptr, 10, 10, 0x0000ffff, "Q W->image quality    A S->zoom    Z X->zoom faster");
	mlx_string_put(ctx_p->mlx_ptr, ctx_p->win_ptr, 10, 30, 0x0000ffff, "C V->color H J->height of 3D object");
	mlx_string_put(ctx_p->mlx_ptr, ctx_p->win_ptr, 10, 50, 0x0000ffff, "direction buttons->move camera      1 2 3 5->move screen of projection");


	mlx_put_image_to_window(ctx_p->mlx_ptr, ctx_p->win_ptr, ctx_p->img_ptr, 0, 100);
}
