/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:04:10 by jleblond          #+#    #+#             */
/*   Updated: 2019/02/22 13:04:11 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_point(float fx, float fy, char *data_addr)
{
	int		i;
	int		x;
	int		y;

	x = fx * WIN_Y;
	y = fy * WIN_Y;

	i = y*WIN_X + x;
	data_addr[2 + i * 4] = 0xff;
}
