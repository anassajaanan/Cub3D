/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:26:34 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 19:34:58 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray_intersection(t_params *params, t_ray *ray, double angle)
{
	t_fpoint	horizontal;
	t_fpoint	vertical;
	double		horizontal_distance;
	double		vertical_distance;

	ray->direction = angle;
	horizontal = horizontal_ray_intersection(params, angle);
	vertical = vertical_ray_intersection(params, angle);
	horizontal_distance = calculate_distance(params->player.x, params->player.y,
			horizontal.x, horizontal.y);
	vertical_distance = calculate_distance(params->player.x, params->player.y,
			vertical.x, vertical.y);
	if (horizontal_distance < vertical_distance)
	{
		ray->x = horizontal.x;
		ray->y = horizontal.y;
		ray->length = horizontal_distance;
		ray->hit = HORIZONTAL;
	}
	else
	{
		ray->x = vertical.x;
		ray->y = vertical.y;
		ray->length = vertical_distance;
		ray->hit = VERTICAL;
	}
}


void	determine_horizontal_texture(t_params *params, t_ray *ray)
{
	t_point	index;

	params->texture_x = (int)ray->x % TILE_SIZE;
	if (params->texture_x > M_PI)
		params->texture_x = TILE_SIZE - params->texture_x - 1;
	index.x = (int)(ray->x) / TILE_SIZE;
	index.y = (int)(ray->y - 0.00001) / TILE_SIZE;
	if (params->map.map_data[index.y][index.x] == '1')
		params->wall_texture = params->south_texture.addr;
	else
		params->wall_texture = params->north_texture.addr;
}

void	determine_vertical_texture(t_params *params, t_ray *ray)
{
	t_point	index;
	
	params->texture_x = (int)ray->y % TILE_SIZE;
	if (ray->direction > M_PI / 2 && ray->direction < 3 * M_PI / 2)
		params->texture_x = TILE_SIZE - params->texture_x - 1;
	index.x = (int)(ray->x - 0.00001) / TILE_SIZE;
	index.y = (int)ray->y / TILE_SIZE;
	if (params->map.map_data[index.y][index.x] == '1')
		params->wall_texture = params->west_texture.addr;
	else
		params->wall_texture = params->east_texture.addr;
}

void	determine_wall_texture(t_params *params, t_ray *ray)
{
	t_point	index;
	
	if (ray->hit == HORIZONTAL)
		determine_horizontal_texture(params, ray);
	else
		determine_vertical_texture(params, ray);
}

void	render_wall_texture(t_params *params, t_ray *ray)
{
	int		y;
	double	texture_step;
	double	texture_pos;
	int		pixel_index;
	int		hex_color;

	y = 0;
	texture_pos = 0;
	texture_step = TEXTURE_SIZE / params->wall_height;
	while (y < params->wall_height)
	{
		params->texture_y = (int)texture_pos & (TEXTURE_SIZE - 1);
		pixel_index = ((int)params->texture_y * TEXTURE_SIZE + (int)params->texture_x) * params->north_texture.bits_per_pixel / 8;
		hex_color = *(unsigned int *)(params->wall_texture + pixel_index);
		mlx_pixel_put_img(params, params->column, params->wall_y + y, hex_color);
		texture_pos += texture_step;
		y++;
	}
}




void	cast_rays(t_params *params)
{
	double	angle;
	double	ray_angle;
	double	column_increment;
	t_ray	ray;

	column_increment = FOV / WINDOW_WIDTH;
	angle = params->player.direction - (FOV / 2);
	for (int column = 0; column < WINDOW_WIDTH; column++)
	{
		ray_angle = angle + (column * column_increment);
		normalize_direction(&ray_angle);
		ray_intersection(params, &ray, ray_angle);
		ray.length *= cos(ray_angle - params->player.direction);
		params->wall_height = (WINDOW_HEIGHT * TILE_SIZE) / ray.length;
		params->wall_y = (WINDOW_HEIGHT / 2) - (params->wall_height / 2);
		params->column = column;
		determine_wall_texture(params, &ray);
		render_wall_texture(params, &ray);

		// // draw ground
		draw_line_img(params, init_point(column, params->wall_y + params->wall_height), init_point(column, WINDOW_HEIGHT), params->floor_color);

		// // draw ceiling
		draw_line_img(params, init_point(column, 0), init_point(column, params->wall_y), params->ceiling_color);
	}
}