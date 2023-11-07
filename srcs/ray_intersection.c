/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:18:37 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/07 17:18:41 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	if ((int)x2 == INT_MAX && (int)y2 == INT_MAX)
		return (INT_MAX);
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

static void	initialize_horizontal_ray(t_params *params, double angle,
		t_fpoint *ray, t_fpoint *step)
{
	double	inv_tan_angle;

	ray->x = INT_MAX;
	ray->y = INT_MAX;
	if (angle == 0 || angle == M_PI || angle == 2 * M_PI)
		return ;
	else if (angle > 0 && angle < M_PI)
	{
		ray->y = (((int)params->player.y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
		step->y = TILE_SIZE;
	}
	else
	{
		ray->y = (((int)params->player.y / TILE_SIZE) * TILE_SIZE) - 0.0001;
		step->y = -TILE_SIZE;
	}
	inv_tan_angle = 1.0 / tan(angle);
	ray->x = params->player.x + (ray->y - params->player.y) * inv_tan_angle;
	step->x = step->y * inv_tan_angle;
}

t_fpoint	horizontal_ray_intersection(t_params *params, double angle)
{
	t_fpoint	ray;
	t_fpoint	step;
	t_point		index;

	initialize_horizontal_ray(params, angle, &ray, &step);
	if (ray.x == INT_MAX && ray.y == INT_MAX)
		return (ray);
	index.x = (int)ray.x / TILE_SIZE;
	index.y = (int)ray.y / TILE_SIZE;
	while (index.x >= 0 && index.x < params->map.cols && index.y >= 0
		&& index.y < params->map.rows)
	{
		if (params->map.map_data[index.y][index.x] == '1')
			return (ray);
		ray.x += step.x;
		ray.y += step.y;
		index.x = (int)ray.x / TILE_SIZE;
		index.y = (int)ray.y / TILE_SIZE;
	}
	ray.x = INT_MAX;
	ray.y = INT_MAX;
	return (ray);
}

static void	initialize_vertical_ray(t_params *params, double angle,
		t_fpoint *ray, t_fpoint *step)
{
	double	tan_angle;

	ray->x = INT_MAX;
	ray->y = INT_MAX;
	if (angle == M_PI / 2 || angle == 3 * M_PI / 2)
		return ;
	else if (angle > M_PI / 2 && angle < 3 * M_PI / 2)
	{
		ray->x = (((int)params->player.x / TILE_SIZE) * TILE_SIZE) - 0.0001;
		step->x = -TILE_SIZE;
	}
	else
	{
		ray->x = (((int)params->player.x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
		step->x = TILE_SIZE;
	}
	tan_angle = tan(angle);
	ray->y = params->player.y + (ray->x - params->player.x) * tan_angle;
	step->y = step->x * tan_angle;
}

t_fpoint	vertical_ray_intersection(t_params *params, double angle)
{
	t_fpoint	ray;
	t_fpoint	step;
	t_point		index;

	initialize_vertical_ray(params, angle, &ray, &step);
	if (ray.x == INT_MAX && ray.y == INT_MAX)
		return (ray);
	index.x = (int)ray.x / TILE_SIZE;
	index.y = (int)ray.y / TILE_SIZE;
	while (index.x >= 0 && index.x < params->map.cols && index.y >= 0
		&& index.y < params->map.rows)
	{
		if (params->map.map_data[index.y][index.x] == '1')
			return (ray);
		ray.x += step.x;
		ray.y += step.y;
		index.x = (int)ray.x / TILE_SIZE;
		index.y = (int)ray.y / TILE_SIZE;
	}
	ray.x = INT_MAX;
	ray.y = INT_MAX;
	return (ray);
}
