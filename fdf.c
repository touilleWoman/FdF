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

int		key_press(int keycode, void *param)
{
	t_context *pctx = (t_context *)param;

	if (keycode == KEYCODE_ESC)
	{
		mlx_destroy_window(pctx->mlx_ptr, pctx->win_ptr);
		exit(0);
	}
	return (0);
}




int		fdf(t_map_params	mpp)
{
	t_context	ctx;
	char		*data_addr;


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

	ctx.mlx_ptr = mlx_init();
	if (ctx.mlx_ptr == 0)
		return (-1);
	ctx.win_ptr = mlx_new_window(ctx.mlx_ptr, WIN_X, WIN_Y, "FdF");
	if (ctx.win_ptr == 0)
		return (-1);
	//mlx_clear_window(ctx.mlx_ptr, ctx.win_ptr);
	ctx.img_ptr = mlx_new_image(ctx.mlx_ptr, WIN_X, WIN_Y);

	data_addr = mlx_get_data_addr(ctx.img_ptr, &ctx.bpp, &ctx.size_line, &ctx.endian);

	// for (int i = 0; i <= 400; ++i)
	// {
	// 	data_addr[2 + i*4] = 0xFF;

	// }

	int		x;
	int		y;
	t_float_point  f_point;


	x = 0;
	y = 0;
	while (y < mpp.y)
	{
		while (x < mpp.x)
		{

			f_point = convert2d(x, y, mpp.map[y][x], mpp); //三者均为坐标值

			draw_point(f_point.x, f_point.y, data_addr);

			x++;
		}
		x = 0;
		y++;
	}


	t_float_point  f_point1;

	x = 0;
	y = 0;
	int	count = 0;
	float  xx;
	float yy;
	while (x < mpp.x)
	{

		f_point = convert2d(x, y, mpp.map[y][x], mpp); //三者均为坐标值



		x++;

		f_point1 = convert2d(x, y, mpp.map[y][x], mpp); //三者均为坐标值

		while ( count <  PRECISION)
		{
			xx = f_point.x + (((f_point1.x - f_point.x)*count)/PRECISION );
			yy = (((f_point1.y - f_point.y) / (f_point1.x - f_point.x)) * (xx - f_point.x)) + f_point.y;
			draw_point( (xx ), (yy ), data_addr);
			count++;
		}
		count = 0;

	}

	// while (y < mpp.y)
	// {
	// 	while (x < mpp.x)
	// 	{

	// 		f_point = convert2d(x, y, mpp.map[y][x], mpp); //三者均为坐标值



	// 		x++;

	// 		f_point1 = convert2d(x, y, mpp.map[y][x], mpp); //三者均为坐标值

	// 	}
	// 	x = 0;
	// 	y++;
	// }



	mlx_put_image_to_window(ctx.mlx_ptr, ctx.win_ptr, ctx.img_ptr, 10, 10);


	//mlx_hook (ctx.win_ptr, 2, 0, key_press, &ctx);
	mlx_key_hook (ctx.win_ptr, key_press, &ctx);

	mlx_loop(ctx.mlx_ptr);
	return (0);
}
