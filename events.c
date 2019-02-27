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
	p->d_ecran = 1.2;
	if (p->mpp.x > p->mpp.y)
		p->cz = p->d_ecran * p->mpp.x;
	else 
		p->cz = p->d_ecran * p->mpp.y;
	
	p->cx = 0;
	p->cy = 0;

	p->preci = 200;
	p->var_z = 0;
	p->var_x = 0;
	p->var_y = 0;
	p->var_cl = 10;
	p->var_fx = 0;
	p->var_fy = 0;
}

void	key_press2(int keycode, t_context *p)
{
	if (keycode == KEYCODE_LEFT)
		p->cx = p->cx - 0.1;
	if (keycode == KEYCODE_RIGHT)
		p->cx = p->cx + 0.1;
	if (keycode == KEYCODE_UP)
		p->cy = p->cy + 0.1;
	if (keycode == KEYCODE_DOWN)
		p->cy = p->cy - 0.1;
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

	if (keycode == KEYCODE_TWO)
		p->var_z++;
	if (keycode == KEYCODE_ONE)
		p->var_z--;
	if (keycode == KEYCODE_Z)
		p->cz--;
	if (keycode == KEYCODE_X)
		p->cz++;

	if ((keycode == KEYCODE_Q) || (keycode == KEYCODE_W))
		key_press3(keycode, p);
	else
		key_press2(keycode, p);
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	ft_bzero(p->data_a, (p->size_l) * WIN_Y);
	draw(p);
	return (0);
}
