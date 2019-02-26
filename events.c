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

void	reset_map(t_context *p)
{
	p->preci = 200;
	p->mpp.d = 2;
	p->var_z = 0;
	p->var_x = 5;
	p->var_y = 0;
	p->var_cl = 10;
	p->var_fx = 0;
	p->var_fy = 0;
	p->angle = 0.57735026919;
}

void	key_press2(int keycode, t_context *p)
{
	if (keycode == KEYCODE_LEFT)
		p->var_x--;
	if (keycode == KEYCODE_RIGHT)
		p->var_x++;
	if (keycode == KEYCODE_UP)
		p->var_y--;
	if (keycode == KEYCODE_DOWN)
		p->var_y++;
	if (keycode == KEYCODE_C)
		p->var_cl = p->var_cl + 10;
	if (keycode == KEYCODE_V)
		p->var_cl = p->var_cl - 10;
	if (keycode == KEYCODE_L)
		p->var_fx = p->var_fx - 0.1;
	if (keycode == KEYCODE_J)
		p->var_fx = p->var_fx + 0.1;
	if (keycode == KEYCODE_I)
		p->var_fy = p->var_fy + 0.1;
	if (keycode == KEYCODE_K)
		p->var_fy = p->var_fy - 0.1;
	if (keycode == KEYCODE_A)
		p->angle = p->angle + 0.01;
	if (keycode == KEYCODE_S)
		p->angle = p->angle - 0.01;
}

void	key_press3(int keycode, t_context *p)
{
	if (keycode == KEYCODE_Q)
		p->preci = p->preci + 20;
	if (keycode == KEYCODE_W)
		p->preci = p->preci - 20;
}

int		key_press(int keycode, void *param)
{
	t_context *p;

	p = (t_context *)param;
	if (keycode == KEYCODE_ESC)
	{
		mlx_destroy_window(p->mlx_ptr, p->win_ptr);
		exit(0);
	}
	if (keycode == KEYCODE_X && (p->mpp.d > 0))
		p->mpp.d = p->mpp.d - 0.2;
	if (keycode == KEYCODE_TWO)
		p->var_z++;
	if (keycode == KEYCODE_ONE)
		p->var_z--;
	if (keycode == KEYCODE_Z)
		p->mpp.d = p->mpp.d + 0.2;
	if ((keycode == KEYCODE_Q) || (keycode == KEYCODE_W))
		key_press3(keycode, p);
	else
		key_press2(keycode, p);
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	ft_bzero(p->data_a, (p->size_l) * WIN_Y);
	draw(p);
	return (0);
}
