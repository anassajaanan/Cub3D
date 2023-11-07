/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:26:34 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/07 10:35:20 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_ray(t_params *params, t_ray *ray, t_fpoint	horizontal,
					t_fpoint vertical)
{
	double		horizontal_distance;
	double		vertical_distance;

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

static void	ray_intersection(t_params *params, t_ray *ray, double angle)
{
	t_fpoint	horizontal;
	t_fpoint	vertical;

	ray->direction = angle;
	horizontal = horizontal_ray_intersection(params, angle);
	vertical = vertical_ray_intersection(params, angle);
	init_ray(params, ray, horizontal, vertical);
	ray->length *= cos(angle - params->player.direction);
}

void	cast_rays(t_params *params)
{
	int		column;
	t_ray	ray;
	double	column_increment;
	double	ray_angle;
	double	angle;

	column = 0;
	column_increment = params->player.fov / WINDOW_WIDTH;
	angle = params->player.direction - (params->player.fov / 2);
	while (column < WINDOW_WIDTH)
	{
		ray_angle = angle + (column * column_increment);
		normalize_direction(&ray_angle);
		ray_intersection(params, &ray, ray_angle);
		determine_wall_texture(params, &ray, &params->wall);
		render_wall_texture(params, &params->wall, column);
		render_ground_and_ceiling(params, &params->wall, column);
		column++;
	}
}
