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
	//float	x_max;
	// int		vfx;
	float	vfy;

	vfy = p->cy * (p->cz - p->d_ecran) / p->cz;
	//printf("vfy%9.6f\n", vfy);
	// vfx = p->cx * (p->cz - p->d_ecran) / p->cz;
	if ((fx <= 0.5 ) && (fx >= -0.5 ) 
		&& fy <=( 0.5 + vfy) && fy >= (-0.5 + vfy) )
	{
	//	printf("fy%9.6f\n", fy);

		xx = (fx  + 0.5) * WIN_X;
		yy = (fy - vfy + 0.5) * WIN_X;
		i =  yy * WIN_X + xx;
		put_color(i, p, z);
	}
}

void		draw_trait(t_float_point fp1, t_float_point fp, t_context *p)
{
	float	vx;
	float	vy;
	float 	vz;

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

void		draw_line(int i, int j, t_context *p, t_float_point fp)
{
	t_float_point	fp1;
	t_float_point	fp2;
	int				x;
	int				y;

	x = i + p->mpp.x / 2;
	y = j + p->mpp.y / 2;

	p->z = p->mpp.map[y][x];
	if (x == p->mpp.x && y != p->mpp.y)
	{
		fp2 = convert2d(i, j + 1, p->mpp.map[y + 1][x], p);
		p->z1 = p->mpp.map[y + 1][x];
		draw_trait(fp2, fp, p);
	}
	if (y == p->mpp.y && x != p->mpp.x)
	{
		fp1 = convert2d((i + 1), j, p->mpp.map[y][x + 1], p);
		p->z1 = p->mpp.map[y][x + 1];
		draw_trait(fp1, fp, p);
	}
	else if (x < p->mpp.x && y < p->mpp.y)
	{
		fp1 = convert2d(i + 1, j, p->mpp.map[y][x + 1], p);
		fp2 = convert2d(i, j + 1, p->mpp.map[y + 1][x], p);
		p->z1 = p->mpp.map[y][x + 1];
		draw_trait(fp1, fp, p);
		p->z1 = p->mpp.map[y + 1][x];
		draw_trait(fp2, fp, p);
	}
}

void		draw(t_context *p)
{
	int				i;
	int				j;
	t_float_point	fp;

	i = 0;
	j = 0;
	while (j < p->mpp.y + 1)
	{
		while (i < p->mpp.x + 1)
		{
			fp = convert2d(i - (p->mpp.x / 2), j - (p->mpp.y / 2), p->mpp.map[j][i], p);
			draw_point(fp.x, fp.y, p, p->mpp.map[j][i]);
			draw_line(i - (p->mpp.x / 2), j - (p->mpp.y / 2), p, fp);
			i++;
		}
		i = 0;
		j++;
	}
	mlx_string_put(p->mlx_ptr, p->win_ptr, 10, 10, 0x0000ffff,
		"Q W->image quality    A S->zoom    Z X->zoom faster");
	mlx_string_put(p->mlx_ptr, p->win_ptr, 10, 30, 0x0000ffff,
		"C V->color 1 2->height of 3D object");
	mlx_string_put(p->mlx_ptr, p->win_ptr, 10, 50, 0x0000ffff,
		"direction buttons->move camera    J K L I->move screen of projection");
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
}
