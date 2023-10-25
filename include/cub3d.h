/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:36:41 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/25 18:38:36 by aajaanan         ###   ########.fr       */
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
	double	focal_length;
	double	range;
}			t_camera;

typedef struct s_ray
{
	double	x;
	double	y;
	double	distance;
	double	direction;
}			t_ray;

typedef struct s_params
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_camera	camera;
}				t_params;


// point.c
t_point	init_point(int x, int y);

// line.c
void	draw_line(t_params *params, t_point p1, t_point p2, int color);


#endif /* CUB3D_H */