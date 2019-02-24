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
	ctx_p->var_y = 0;

	ctx_p->temp = 0;
	ctx_p->var_cl = 10;
	ctx_p->var_fx = 0;
	ctx_p->var_fy = 0;
	ctx_p->angle = 0.57735026919;




}

int		key_press(int keycode, void *param)
{
	t_context *ctx_p = (t_context *)param;

	if (keycode == KEYCODE_ESC)
	{
		mlx_destroy_window(ctx_p->mlx_ptr, ctx_p->win_ptr);
		exit(0);
	}
	if (keycode == KEYCODE_Q)
		ctx_p->preci = ctx_p->preci + 30;
	if (keycode == KEYCODE_W)
		ctx_p->preci = ctx_p->preci - 30;
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
	if (keycode == KEYCODE_UP)
		ctx_p->var_y --;
	if (keycode == KEYCODE_DOWN)
		ctx_p->var_y ++;
	if (keycode == KEYCODE_UP)
		ctx_p->temp = ctx_p->temp + 5;
	if (keycode == KEYCODE_DOWN)
		ctx_p->temp = ctx_p->temp - 5;
	if (keycode == KEYCODE_C)
		ctx_p->var_cl = ctx_p->var_cl + 10;
	if (keycode == KEYCODE_V)
		ctx_p->var_cl = ctx_p->var_cl - 10;
	if (keycode == KEYCODE_THREE)
		ctx_p->var_fx = ctx_p->var_fx + 0.1 ;
	if (keycode == KEYCODE_ONE)
		ctx_p->var_fx = ctx_p->var_fx - 0.1 ;
	if (keycode == KEYCODE_FIVE)
		ctx_p->var_fy = ctx_p->var_fy + 0.1 ;
	if (keycode == KEYCODE_TWO)
		ctx_p->var_fy = ctx_p->var_fy - 0.1 ;
	if (keycode == KEYCODE_A)
		ctx_p->angle = ctx_p->angle - 0.01 ;
	if (keycode == KEYCODE_S)
		ctx_p->angle = ctx_p->angle - 0.01 ;
	mlx_clear_window(ctx_p->mlx_ptr, ctx_p->win_ptr);
	ft_bzero(ctx_p->data_addr, (ctx_p->size_line) * WIN_Y);
	draw(ctx_p);
	return (0);
}



