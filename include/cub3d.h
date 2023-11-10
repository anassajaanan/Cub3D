/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 13:36:41 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/10 14:40:22 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/include/libft.h"
# include "../lib/mlx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 1024
# define RESOLUTION 1024
# define TILE_SIZE 64
# define TEXTURE_SIZE 64
# define MOVE_SPEED 40
# define ROTATE_SPEED 0.1

# define HORIZONTAL 0
# define VERTICAL 1

typedef enum e_error
{
	SUCCESS,
	INVALID_ARG,
	WRONG_MAP,
	WRONG_INPUT,
	MALLOC_FAIL,
	IMG_FAIL,
	OPEN_ERR,
	MLX_FAIL,
	WRITE_FAIL,
	WRONG_TEXTURE
}						t_error;

// #===========# queue.c #===============#
typedef struct s_queue_node
{
	char				*val;
	struct s_queue_node	*next;
}						t_queue_node;

typedef struct s_queue
{
	t_queue_node		*front;
	t_queue_node		*rear;
}						t_queue;

void					init_queue(t_queue *q);
void					enqueue(t_queue *q, void *val);
void					*dequeue(t_queue *q);
char					*queue_to_str(t_queue *q);
void					free_queue(t_queue *q);
// #===========# queue.c #===============#

// #===========# parsing.c #=============#

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_fpoint
{
	float				x;
	float				y;
}						t_fpoint;

typedef struct s_color
{
	int					red;
	int					green;
	int					blue;
}						t_color;

typedef struct s_map_infos
{
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;

	t_color				floor_color;
	t_color				ceiling_color;

	t_queue				queue;

	int					parsed_color_count;
	int					parsed_texture_count;
}						t_map_infos;

typedef struct s_map
{
	int					cols;
	int					rows;
	char				**map_data;
}						t_map;

typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					bpp;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_img;

typedef struct s_player
{
	double				x;
	double				y;
	double				dx;
	double				dy;
	double				direction;
	double				fov;
}						t_player;

typedef struct s_ray
{
	double				x;
	double				y;
	double				direction;
	double				length;
	int					hit;
}						t_ray;

typedef struct s_wall
{
	double				wall_height;
	char				*wall_texture;
	t_img				*texture_img;
	int					texture_x;
	int					texture_y;
	int					wall_y;
}						t_wall;

typedef struct s_params
{
	void				*mlx;
	void				*win;
	t_img				window_img;

	t_map				map;
	t_map_infos			map_infos;

	t_player			player;
	t_ray				ray;

	t_img				north_texture;
	t_img				south_texture;
	t_img				west_texture;
	t_img				east_texture;

	int					floor_color;
	int					ceiling_color;

	t_wall				wall;

}						t_params;

// #============# free.c #===============#
void					ft_free(void *ptr);
void					free_split_array(char **array);
void					free_and_cleanup(t_params *params);
void					free_2d_array(char **map);
void					free_map_infos(t_map_infos *map_infos);

// #============# parsing.c #===============#
int						parse_map(char *file_name, t_map_infos *map_infos);

// #============# parsing_validation.c #===============#
int						validate_colors(t_color *color, char **colors);
int						is_valid_texture_path(char *path);

// #============# parsing_helpers.c #===============#
int						startswith(char **array, char *str);
int						array_size(char **array);
int						is_empty_line(char *line);
int						open_map_file(char *file_name);
int						is_numeric(char *str);

// #============# map_validation.c #===============#
int						is_valid_map(t_map *map);

// #============# init.c #===============#
void					init_player(t_params *params);
void					init_params(t_params *params);
void					init_colors(t_params *params);

// #============# map.c #===============#
void					convert_queue_to_2d_array(t_map *map, t_queue *queue);

// point.c
t_point					init_point(int x, int y);
int						mlx_pixel_put_img(t_params *params, int x, int y,
							int color);

// line.c
void					draw_line(t_params *params, t_point p1, t_point p2,
							int color);
void					draw_line_img(t_params *params, t_point p1, t_point p2,
							int color);

// raycasting.c
void					cast_rays(t_params *params);

// player_mouvements.c
void					look_left(t_params *params);
void					look_right(t_params *params);
void					move_up(t_params *params);
void					move_down(t_params *params);
void					move_left(t_params *params);
void					move_right(t_params *params);

// player_actions.c
void					normalize_direction(double *direction);
void					look_left(t_params *params);
void					look_right(t_params *params);

// init_images.c
int						init_images(t_params *params);

// ray_intersections.c
double					calculate_distance(double x1, double y1, double x2,
							double y2);
t_fpoint				horizontal_ray_intersection(t_params *params,
							double angle);
t_fpoint				vertical_ray_intersection(t_params *params,
							double angle);

// rendering.c
void					determine_wall_texture(t_params *params, t_ray *ray,
							t_wall *wall);
void					render_wall_texture(t_params *params, t_wall *wall,
							int column);
void					render_ground_and_ceiling(t_params *params,
							t_wall *wall, int column);

// hook.c
int						key_hook(int keycode, t_params *params);
int						update_window(t_params *params);
int						close_window(t_params *params);

#endif /* CUB3D_H */