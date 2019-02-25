/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 14:28:02 by jleblond          #+#    #+#             */
/*   Updated: 2019/02/21 14:28:05 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_float_point convert2d(int x, int y, int z, t_context *p)
{
	t_float_point  f_point;
	int				z1;

	if (z != p->mpp.z_min)
	{
		z1 = ((p->mpp.d) * ((p->mpp.x) - 1)) - (z + p->var_z);
	}
	else
	{
		z1 = ((p->mpp.d) * ((p->mpp.x) - 1)) - z ;

	}
	x = x + p->var_x;
	y = y + p->var_y;
	f_point.x = x / (z1 * p->angle) + p->var_fx;
	f_point.y = y / (z1 * p->angle) + p->var_fy;
	return (f_point);
}


t_color		color_val_calculate(int  val_cl)
{
	t_color		cl;

	if(val_cl < 0)
		val_cl = - val_cl;
	while (val_cl > 360)
		val_cl = val_cl - 360;
	if (val_cl >= 0 && val_cl < 121)
	{
		cl.b = 0;
		cl.g = val_cl * (255 / 120);
		cl.r = 255 - cl.g;
	}
	else if (val_cl < 240)
	{
		cl.b = (val_cl - 120) * 255 / 120;
		cl.g = 255 - cl.b;
		cl.r = 0;
	}
	else
	{
		cl.r = (val_cl - 240) * 255 /120;
		cl.g = 0;
		cl.b = 255 -cl.r;
	}
	return (cl);
}
