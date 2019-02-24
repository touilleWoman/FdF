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


void	get_maxmin_z(t_context *ctx_p)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (j < ctx_p->mpp.y)
	{
		while (i < ctx_p->mpp.x)
		{

			if ((i == 0) && (j == 0))
			{
				ctx_p->mpp.z_max = ctx_p->mpp.map[j][i];
				ctx_p->mpp.z_min = ctx_p->mpp.map[j][i];
			}
			else if (ctx_p->mpp.map[j][i] > ctx_p->mpp.z_max)
				ctx_p->mpp.z_max = ctx_p->mpp.map[j][i];
			else if (ctx_p->mpp.map[j][i] < ctx_p->mpp.z_max)
				ctx_p->mpp.z_min = ctx_p->mpp.map[j][i];
			i++;
		}
		i = 0;
		j++;
	}
}

int		fdf(t_map_params	mpp)
{
	t_context	ctx;


// //test to show map stocké
// 	printf("%mppx:%dmppy:%d\n",mpp.x, mpp.y); //mpp.x et mpp.y sont nombre de point
// 	for (int i = 0; i < mpp.y; ++i)
// 	{
// 		for (int a = 0; a < mpp.x; ++a)
// 		{
// 			printf("%d", mpp.map[i][a]);
// 		}
// 		printf("\n");
// 	}
	ctx.mpp = mpp;
	get_maxmin_z(&ctx);
	//printf("z_max:%d   z_min:%d\n", ctx.mpp.z_max, ctx.mpp.z_min);
	ctx.mlx_ptr = mlx_init();
	if (ctx.mlx_ptr == 0)
		return (-1);
	ctx.win_ptr = mlx_new_window(ctx.mlx_ptr, WIN_X, WIN_Y, WIN_NAME);
	if (ctx.win_ptr == 0)
		return (-1);
	//mlx_clear_window(ctx.mlx_ptr, ctx.win_ptr);
	ctx.img_ptr = mlx_new_image(ctx.mlx_ptr, WIN_X, WIN_Y);

	ctx.data_addr = mlx_get_data_addr(ctx.img_ptr, &ctx.bpp, &ctx.size_line, &ctx.endian);
	reset_map(&ctx);

	draw(&ctx);







	mlx_hook (ctx.win_ptr, 2, 0, key_press, &ctx);
	//mlx_key_hook (ctx.win_ptr, key_press, &ctx);

	mlx_loop(ctx.mlx_ptr);
	return (0);
}
