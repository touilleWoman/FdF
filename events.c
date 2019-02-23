/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:00:50 by jleblond          #+#    #+#             */
/*   Updated: 2019/02/22 17:00:51 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_map(t_context *ctx_p)
{
	ctx_p->preci = 100;
}

int		key_press(int keycode, void *param)
{
	t_context *ctx_p = (t_context *)param;

	if (keycode == KEYCODE_ESC)
	{
		mlx_destroy_window(ctx_p->mlx_ptr, ctx_p->win_ptr);
		exit(0);
	}
	if (keycode == KEYCODE_P)
	{
		ctx_p->preci = ctx_p->preci + 100;
	}
	mlx_clear_window(ctx_p->mlx_ptr, ctx_p->win_ptr);
	draw(ctx_p);

	return (0);
}



