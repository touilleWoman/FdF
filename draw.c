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

void		put_color(int i, t_context *p, float z)
{
	t_color		cl;
	int			range;

	range = 120 * z / (p->mpp.z_max - p->mpp.z_min) + p->var_cl;
	cl = color_val_calculate(range);
	p->data_a[i * 4 + 2] = cl.r;
	p->data_a[i * 4 + 1] = cl.g;
	p->data_a[i * 4] = cl.b;
}

void		draw_point(float fx, float fy, t_context *p, float z)
{
	int		i;
	int		xx;
	int		yy;
	float	x_max;

	x_max = (p->mpp.x - 1.0) / (p->mpp.y - 1);
	if ((fy > 1) || (fy < 0) || (fx < 0) || (fx > x_max))
		return ;
	xx = fx * WIN_Y;
	yy = fy * WIN_Y;
	if ((xx >= 1200) || (yy >= 900))
		return ;
	i = yy * WIN_X + xx;
	put_color(i, p, z);
}

void		draw_trait(t_float_point fp1, t_float_point fp, t_context *p, int z, int z1)
{
	int		count;
	float	x;
	float	y;
	float 	zz;

	count = 0;
	while (count < (p->preci))
	{
		if (fp1.x != fp.x)
		{
			x = fp.x + (((fp1.x - fp.x) * count) / (p->preci) );
			y = (((fp1.y - fp.y) / (fp1.x - fp.x)) * (x - fp.x)) + fp.y;
			if (fp1.y != fp.y)
				zz = z + (z1 - z) * count * 1.0 / p->preci;
			else
				zz = z;
			draw_point(x, y, p, zz);
		}
		else
		{
			x = fp.x;
			y = fp.y + (((fp1.y - fp.y) * count) / (p->preci));
			draw_point(x, y, p, z);
		}
		count++;
	}
}

void		draw_line(int x, int y, t_context *p, t_float_point fp)
{
	t_float_point	fp1;
	t_float_point	fp2;

	if (x == (p->mpp.x - 1) && y != (p->mpp.y - 1))
	{
		fp2 = convert2d(x, y + 1, p->mpp.map[y + 1][x], p);
		draw_trait(fp2, fp, p, p->mpp.map[y][x], p->mpp.map[y + 1][x]);
	}
	if (y == (p->mpp.y - 1) && x != (p->mpp.x - 1))
	{
		fp1 = convert2d((x + 1), y, p->mpp.map[y][x + 1], p);
		draw_trait(fp1, fp, p, p->mpp.map[y][x], p->mpp.map[y][x + 1]);
	}
	else if (x < (p->mpp.x - 1) && y < (p->mpp.y - 1))
	{
		fp1 = convert2d((x + 1), y, p->mpp.map[y][x + 1], p);
		fp2 = convert2d(x, y + 1, p->mpp.map[y + 1][x], p);
		draw_trait(fp1, fp, p, p->mpp.map[y][x], p->mpp.map[y][x + 1]);
		draw_trait(fp2, fp, p, p->mpp.map[y][x], p->mpp.map[y + 1][x]);
	}
}

void		draw(t_context *p)
{
	int				x;
	int				y;
	t_float_point	fp;

	x = 0;
	y = 0;
	while (y < p->mpp.y)
	{
		while (x < p->mpp.x)
		{
			fp = convert2d(x, y, p->mpp.map[y][x], p);
			draw_point(fp.x, fp.y, p, p->mpp.map[y][x]);
			draw_line(x, y, p, fp);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_string_put(p->mlx_ptr, p->win_ptr, 10, 10, 0x0000ffff,
		"Q W->image quality    A S->zoom    Z X->zoom faster");
	mlx_string_put(p->mlx_ptr, p->win_ptr, 10, 30, 0x0000ffff,
		"C V->color H J->height of 3D object");
	mlx_string_put(p->mlx_ptr, p->win_ptr, 10, 50, 0x0000ffff,
		"direction buttons->move camera    1 2 3 5->move screen of projection");
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 100);
}
