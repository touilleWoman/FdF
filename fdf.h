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
# define KEYCODE_P 35


# define WIN_X 1200
# define WIN_Y 900
//# define IMG_X 400
//# define IMG_Y 300
# define ANGLE 0.57735026919
 // angle de vu = 60degree  ANGLE = tan(angle de vu / 2)
# define D 2
# define PRECISION 1000



typedef struct context
{
	void *mlx_ptr;
	void *win_ptr;
	int	bpp;
	int	size_line;
	int	endian;
	void *img_ptr;
	int		preci;
	int		d;
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

// typedef struct event
// {
// 	int		preci;
// 	int		d;
// }				t_event;


t_map_params	load_map(char *argv);
int				fdf(t_map_params	mpp);
t_float_point convert2d(int x, int y, int z, t_map_params mpp);
void	draw_point(float fx, float fy, char *data_addr);
void	draw(t_map_params	mpp, char *data_addr, t_context *ctx_p);
void	draw_trait(t_float_point  fp1, t_float_point  fp, char *data_addr, t_context *ctx_p);
void	reset_map(t_context *ctx_p);


#endif