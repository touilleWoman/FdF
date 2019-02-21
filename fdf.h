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

# define WIN_X 1200
# define WIN_Y 900
# define IMG_X 400
# define IMG_Y 300
# define RADIANT 1.0471975512 // 60degree



typedef struct context
{
	void *mlx_ptr;
	void *win_ptr;
} 			t_context;

typedef struct map_params
{
	int			x;
	int			y;
	int			ret;
	int			**map;
} 			t_map_params;

typedef struct float_point
{
	float		x;
	float		y;
}			t_float_point;

t_map_params	load_map(char *argv);
int				fdf(t_map_params	mpp);
t_float_point convert2d(int x, int y, int z);


#endif