/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycasting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:51:58 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 19:33:40 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>


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
		mlx_pixel_put_img(params, column, params->wall_y + y, hex_color);
		texture_pos += texture_step;
		y++;
	}
}