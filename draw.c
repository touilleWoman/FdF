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

void		draw_point(float fx, float fy, t_context *p, float z)
{
	int		i;
	int		xx;
	int		yy;

	if ((fy > 1) || (fy < 0) || (fx < 0) || (fx > 1))
		return ;
	xx = fx * WIN_X;
	yy = fy * WIN_X;
	if ((xx >= 1200) || (yy >= 900))
		return ;
	i = yy * WIN_X + xx;
	put_color(i, p, z);
}

void		draw_trait(t_float_point fp1, t_float_point fp, t_context *p)
{
	float	vx;
	float	vy;
	float   vz;

	p->count = 0;

	while (p->count < (p->preci))
	{
		vz = p->z + (p->z1 - p->z) * p->count * 1.0 / p->preci;

		if (fp1.x != fp.x)
		{
			vx = fp.x + (((fp1.x - fp.x) * p->count) / (p->preci));
			vy = (((fp1.y - fp.y) / (fp1.x - fp.x)) * (vx - fp.x)) + fp.y;
			draw_point(vx, vy, p, vz);
		}
		else
		{
			vx = fp.x;
			vy = fp.y + (((fp1.y - fp.y) * p->count) / (p->preci));
			draw_point(vx, vy, p, vz);
		}
		p->count++;
	}
}

void		draw_line(int x, int y, t_context *p, t_float_point fp)
{
	t_float_point	fp1;
	t_float_point	fp2;

	p->z = p->mpp.map[y][x];
	if (x == (p->mpp.x - 1) && y != (p->mpp.y - 1))
	{
		fp2 = convert2d(x, y + 1, p->mpp.map[y + 1][x], p);
		p->z1 = p->mpp.map[y + 1][x];
		draw_trait(fp2, fp, p);
	}
	if (y == (p->mpp.y - 1) && x != (p->mpp.x - 1))
	{
		fp1 = convert2d((x + 1), y, p->mpp.map[y][x + 1], p);
		p->z1 = p->mpp.map[y][x + 1];
		draw_trait(fp1, fp, p);
	}
	else if (x < (p->mpp.x - 1) && y < (p->mpp.y - 1))
	{
		fp1 = convert2d((x + 1), y, p->mpp.map[y][x + 1], p);
		fp2 = convert2d(x, y + 1, p->mpp.map[y + 1][x], p);
		p->z1 = p->mpp.map[y][x + 1];
		draw_trait(fp1, fp, p);
		p->z1 = p->mpp.map[y + 1][x];
		draw_trait(fp2, fp, p);
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
		"Q W->image quality    Z X->zoom in    X->zoom out  A S->zoom slower");
	mlx_string_put(p->mlx_ptr, p->win_ptr, 10, 30, 0x0000ffff,
		"C V->color 1 2->height of 3D object");
	mlx_string_put(p->mlx_ptr, p->win_ptr, 10, 50, 0x0000ffff,
		"direction keys->move camera    J K L I->move screen of projection");
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 100);
}
