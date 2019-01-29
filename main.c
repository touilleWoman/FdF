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

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>


#define ESC_KEYCODE 0x35


typedef struct context
{
	void *mlx_ptr;
	void *win_ptr;	
} 			t_context;


void	key_hook(int keycode, void *param)
{
	t_context *pctx = (t_context *)param;

	if (keycode == ESC_KEYCODE)
	{
		mlx_destroy_window(pctx->mlx_ptr, pctx->win_ptr);
		exit(0);
	}
}

int		main()
{
	t_context ctx;
	
	ctx.mlx_ptr = mlx_init();
	if (ctx.mlx_ptr == 0)
		return (1);

	ctx.win_ptr = mlx_new_window(ctx.mlx_ptr, 600, 600, "FdF");
	if (ctx.win_ptr == 0)
		return (1);
	mlx_pixel_put(ctx.mlx_ptr, ctx.win_ptr, 100, 300, 0x00AAAAAA);
	mlx_key_hook (ctx.win_ptr, (int (*)())key_hook, &ctx);

	mlx_loop(ctx.mlx_ptr);
	return (0);
}
