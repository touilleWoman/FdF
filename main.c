/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:36:08 by jleblond          #+#    #+#             */
/*   Updated: 2019/01/15 15:36:10 by jleblond         ###   ########.fr       */
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



int		fdf()
{
	t_context	ctx;
	void		*img_ptr;
	int			bits_per_pixel;
	int			size_line;
	int 		endian;
	char		*data_addr;

	ctx.mlx_ptr = mlx_init();
	if (ctx.mlx_ptr == 0)
		return (-1);
	ctx.win_ptr = mlx_new_window(ctx.mlx_ptr, 900, 900, "FdF");
	if (ctx.win_ptr == 0)
		return (-1);
	mlx_clear_window(ctx.mlx_ptr, ctx.win_ptr);
	img_ptr = mlx_new_image(ctx.mlx_ptr, 400, 400);

	data_addr = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
	printf("%d %d %d\n", bits_per_pixel, size_line, endian);
	
	data_addr[2] =0xFF;
	data_addr[6] =0xFF;
	data_addr[10] =0xFF;
	data_addr[802] =0xFF;
	data_addr[806] =0xFF;
	data_addr[810] =0xFF;

	// for (int i = 0; i <= 1800; ++i)
	// {
	// 	data_addr[2 + i*4] = 0xFF;

	// }
	int	color_value = 0;

	color_value = mlx_get_color_value(ctx.mlx_ptr, 0xff0000);
	printf("color_va==%d\n", color_value );


	mlx_put_image_to_window(ctx.mlx_ptr, ctx.win_ptr, img_ptr, 50, 50);


	//mlx_hook (ctx.win_ptr, 2, 0, key_press, &ctx);
	mlx_key_hook (ctx.win_ptr, key_press, &ctx);

	mlx_loop(ctx.mlx_ptr);
	return (0);
}

int main(int argc, char **argv)
{
	int		ret;

	if (argc != 2)
	{
		ft_putendl("Usage : ./fdf <map file name>");
		return (0);
	}
	if (stock_map(argv[1]) == -1)
	{
		ft_putendl("wrong map");
		return (0);
	}
	ret = fdf();
	if (ret == -1)
	{
		printf("error");
	}
	return (0);
}

