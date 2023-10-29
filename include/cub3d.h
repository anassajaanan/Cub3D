/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:36:41 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/29 16:58:44 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include "../lib/libft/include/libft.h"
# include "../lib/mlx/mlx.h"

#define HORIZONTAL 0
#define VERTICAL 1

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_fpoint
{
	float	x;
	float	y;
}			t_fpoint;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	direction;
}			t_player;

typedef struct s_camera
{
	int		resolution;
}			t_camera;

typedef struct s_ray
{
	double	x;
	double	y;
	double	distance;
	double	direction;
	int		color;
	int 	hit;
}			t_ray;

typedef struct s_params
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_camera	camera;
	t_img		img;
}				t_params;


// point.c
t_point	init_point(int x, int y);
int	mlx_pixel_put_img(void *mlx_ptr, t_img *img_ptr, int x, int y, int color);

// line.c
void	draw_line(t_params *params, t_point p1, t_point p2, int color);
void	draw_line_img(t_params *params, t_point p1, t_point p2, int color);


#endif /* CUB3D_H */