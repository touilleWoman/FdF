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

# include "fdf.h"



t_float_point convert2d(int x, int y, int z, t_context *ctx_p)
{
	t_float_point  f_point;
	int				z1;

	if (z != ctx_p->mpp.z_min)
	{
		z1 = ((ctx_p->mpp.d) * ((ctx_p->mpp.x) - 1)) - (z + ctx_p->var_z);
	}
	else
	{
		z1 = ((ctx_p->mpp.d) * ((ctx_p->mpp.x) - 1)) - z ;

	}
	//printf("z:%d\n", z );
	//ar = ((mpp.x - 1.0) / (mpp.y -1)); // 常量，后面可以移出去

	x = x + ctx_p->var_x;
	y = y + ctx_p->var_y;

	f_point.x = x / (z1 * ctx_p->angle) + ctx_p->var_fx; //f_point.y 在0 到1 之间
	f_point.y = y / (z1 * ctx_p->angle) + ctx_p->var_fy;

	return (f_point);

}


