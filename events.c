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
	ctx_p->mpp.d = 2;
	ctx_p->var_z = 0;
	ctx_p->var_x = 0;


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
		ctx_p->preci = ctx_p->preci + 50;
	if (keycode == KEYCODE_O)
		ctx_p->preci = ctx_p->preci - 50;
	if (keycode == KEYCODE_Z)
		ctx_p->mpp.d = ctx_p->mpp.d + 0.2;
	if (keycode == KEYCODE_X && ctx_p->mpp.d > 0)
		ctx_p->mpp.d = ctx_p->mpp.d - 0.2;
	if (keycode == KEYCODE_H)
		ctx_p->var_z++;
		// = ctx_p->var_z + 1;
	if (keycode == KEYCODE_J)
		ctx_p->var_z = ctx_p->var_z - 1;
	if (keycode == KEYCODE_LEFT)
		ctx_p->var_x --;
	if (keycode == KEYCODE_RIGHT)
		ctx_p->var_x ++;
	mlx_clear_window(ctx_p->mlx_ptr, ctx_p->win_ptr);
	ft_bzero(ctx_p->data_addr, (ctx_p->size_line) * WIN_Y);
	draw(ctx_p);
	return (0);
}



