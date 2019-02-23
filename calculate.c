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



t_float_point convert2d(int x, int y, int z, t_map_params mpp)
{
	float 			ar;
	t_float_point  f_point;
	int				z1;


	z1 = (D * (mpp.x - 1)) - z; // 常量，后面可以移出去
//	printf("z1:%d\n", z1 );
	ar = ((mpp.x - 1.0) / (mpp.y -1)); // 常量，后面可以移出去
	f_point.x = x / (z1 * ANGLE); //f_point.y 在0 到1 之间
	f_point.y = y / (z1 * ANGLE);
//	printf("float x:%9.6ffloat y:%9.6f\n", f_point.x, f_point.y );

	return (f_point);

}


