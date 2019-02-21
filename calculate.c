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



t_float_point convert2d(int x, int y, int z)
{
	float 			ar;
	t_float_point  f_point;
	int				z1;

	z1 = 20 - z;
	ar = IMG_X / IMG_Y;
	f_point.x = x / (ar * z1 * tan(RADIANT / 2));
	f_point.y = y / (z1 * tan(RADIANT / 2));
	printf("float x:%9.6ffloat y:%9.6f\n", f_point.x, f_point.y );

	return (f_point);

}



