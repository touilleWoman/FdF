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






	mlx_put_image_to_window(ctx.mlx_ptr, ctx.win_ptr, ctx.img_ptr, 10, 10);


	mlx_hook (ctx.win_ptr, 2, 0, key_press, &ctx);
	//mlx_key_hook (ctx.win_ptr, key_press, &ctx);

	mlx_loop(ctx.mlx_ptr);
	return (0);
}
