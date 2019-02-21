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


void	draw_point(int x, int y, char *data_addr)
{
	int		i;

	i = y*IMG_X + x;
	data_addr[2 + i * 4] = 0xff;
}


int		fdf(t_map_params	mpp)
{
	t_context	ctx;
	void		*img_ptr;
	int			bits_per_pixel;
	int			size_line;
	int 		endian;
	char		*data_addr;



//test to show map stocké
	printf("%mppx:%dmppy:%d\n",mpp.x, mpp.y);
	for (int i = 0; i < mpp.y; ++i)
	{
		for (int a = 0; a < mpp.x; ++a)
		{
			printf("%d", mpp.map[i][a]);
		}
		printf("\n");
	}



	ctx.mlx_ptr = mlx_init();
	if (ctx.mlx_ptr == 0)
		return (-1);
	ctx.win_ptr = mlx_new_window(ctx.mlx_ptr, WIN_X, WIN_Y, "FdF");
	if (ctx.win_ptr == 0)
		return (-1);
	mlx_clear_window(ctx.mlx_ptr, ctx.win_ptr);
	img_ptr = mlx_new_image(ctx.mlx_ptr, IMG_X, IMG_Y);

	data_addr = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
	//printf("%d %d %d\n", bits_per_pixel, size_line, endian);

	// for (int i = 0; i <= 400; ++i)
	// {
	// 	data_addr[2 + i*4] = 0xFF;

	// }


	draw_point(0, 0, data_addr);
	draw_point(399, 0, data_addr);
	draw_point(0, 299, data_addr);
	draw_point(399, 299, data_addr);

	int		x;
	int		y;
	t_float_point  f_point;


	x = 0;
	y = 0;
	while (y < mpp.y)
	{
		while (x < mpp.x)
		{

			f_point = convert2d(x, y, mpp.map[y][x]);
			//((x * IMG_X) / mpp.x, (y * IMG_Y) / mpp.y , mpp.map[y][x]);


			draw_point((f_point.x * IMG_X) / mpp.x, (f_point.y * IMG_Y) / mpp.y , data_addr);

		//	(f_point.x, f_point.y, data_addr);
			x++;
		}
		x = 0;
		y++;
	}




	mlx_put_image_to_window(ctx.mlx_ptr, ctx.win_ptr, img_ptr, (WIN_X/3), (WIN_Y/3));


	//mlx_hook (ctx.win_ptr, 2, 0, key_press, &ctx);
	mlx_key_hook (ctx.win_ptr, key_press, &ctx);

	mlx_loop(ctx.mlx_ptr);
	return (0);
}
