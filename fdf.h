/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:06:17 by jleblond          #+#    #+#             */
/*   Updated: 2019/02/18 15:06:18 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_H
# define FDF_H



# include "mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

# define KEYCODE_ESC 53


typedef struct context
{
	void *mlx_ptr;
	void *win_ptr;
} 			t_context;

typedef struct coordinate3d
{
	int	x;
	int	y;
	int	z;
} 			t_coordinate3d;

int		stock_map(char *str);


#endif