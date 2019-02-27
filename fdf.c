/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 14:59:59 by jleblond          #+#    #+#             */
/*   Updated: 2019/02/20 15:00:01 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		get_maxmin_z(t_context *p)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (j < p->mpp.y + 1)
	{
		while (i < p->mpp.x + 1)
		{
			if ((i == 0) && (j == 0))
			{
				p->mpp.z_max = p->mpp.map[j][i];
				p->mpp.z_min = p->mpp.map[j][i];
			}
			else if (p->mpp.map[j][i] > p->mpp.z_max)
				p->mpp.z_max = p->mpp.map[j][i];
			else if (p->mpp.map[j][i] < p->mpp.z_min)
				p->mpp.z_min = p->mpp.map[j][i];
			i++;
		}
		i = 0;
		j++;
	}
	printf("zmax%d   zmin%d\n", p->mpp.z_max, p->mpp.z_min );
}

int			fdf(t_map_params mpp)
{
	t_context	ctx;

	ctx.mpp = mpp;
	get_maxmin_z(&ctx);
	ctx.mlx_ptr = mlx_init();
	if (ctx.mlx_ptr == 0)
		return (-1);
	ctx.win_ptr = mlx_new_window(ctx.mlx_ptr, WIN_X, WIN_Y, WIN_NAME);
	if (ctx.win_ptr == 0)
		return (-1);
	ctx.img_ptr = mlx_new_image(ctx.mlx_ptr, WIN_X, WIN_Y);
	ctx.data_a = mlx_get_data_addr(ctx.img_ptr, &ctx.bpp, &ctx.size_l, &ctx.e);
	reset_map(&ctx);
	draw(&ctx);
	mlx_hook(ctx.win_ptr, 2, 0, key_press, &ctx);
	mlx_loop(ctx.mlx_ptr);
	return (0);
}
