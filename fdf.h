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
# define KEYCODE_Z 6
# define KEYCODE_X 7
# define KEYCODE_UP 126
# define KEYCODE_DOWN 125
# define KEYCODE_LEFT 123
# define KEYCODE_RIGHT 124
# define KEYCODE_Q 12
# define KEYCODE_W 13
# define KEYCODE_A 0
# define KEYCODE_S 1
# define KEYCODE_C 8
# define KEYCODE_V 9
# define KEYCODE_ONE 18
# define KEYCODE_TWO 19
# define KEYCODE_J 38
# define KEYCODE_K 40
# define KEYCODE_L 37
# define KEYCODE_I 34
# define WIN_X 1200
# define WIN_Y 900
# define ANGLE 0.57735026919
# define WIN_NAME "fdf"

typedef struct		map_params
{
	int				x;
	int				y;
	int				ret;
	float			d;
	int				**map;
	int				z_max;
	int				z_min;
}					t_map_params;

typedef struct		float_point
{
	float			x;
	float			y;
}					t_float_point;


typedef struct		context
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				bpp;
	int				size_l;
	int				e;
	void 			*img_ptr;
	int				preci;
	char			*data_a;
	int				var_z;
	t_map_params 	mpp;
	int				var_x;
	int				var_y;
	int				temp;
	int				var_cl;
	float			var_fx;
	float			var_fy;
	float			angle;
	int				count;
}					t_context;

typedef struct 		color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

t_map_params		load_map(char *argv);
int					fdf(t_map_params	mpp);
t_float_point		convert2d(int x, int y, int z, t_context *p);
void				draw(t_context *p);
void				draw_trait(t_float_point fp1, t_float_point fp, t_context *p, int z, int z1);
void				reset_map(t_context *p);
int					key_press(int keycode, void *param);
void				draw_point(float fx, float fy, t_context *p, float z);
t_color				color_val_calculate(int  val_cl);
void				put_color(int i, t_context *p, float z);
#endif
