/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:24:33 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/11 14:07:02 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_up(t_params *params)
{
	int	x;
	int	y;

	x = (int)(params->player.x + params->player.dx) / TILE_SIZE;
	y = (int)(params->player.y + params->player.dy) / TILE_SIZE;
	if (params->map.map_data[y][x] == '0')
	{
		params->player.x += params->player.dx;
		params->player.y += params->player.dy;
		cast_rays(params);
	}
}

void	move_down(t_params *params)
{
	int	x;
	int	y;

	x = (int)(params->player.x - params->player.dx) / TILE_SIZE;
	y = (int)(params->player.y - params->player.dy) / TILE_SIZE;
	if (params->map.map_data[y][x] == '0')
	{
		params->player.x -= params->player.dx;
		params->player.y -= params->player.dy;
		cast_rays(params);
	}
}

void	move_left(t_params *params)
{
	double	x;
	double	y;
	double	sin_value;
	double	cos_value;

	sin_value = sin(params->player.direction + M_PI / 2) * MOVE_SPEED;
	cos_value = cos(params->player.direction + M_PI / 2) * MOVE_SPEED;
	y = (params->player.y - sin_value) - 0.0001;
	x = (params->player.x - cos_value) - 0.0001;
	if (params->map.map_data[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '0')
	{
		params->player.x -= cos_value;
		params->player.y -= sin_value;
		cast_rays(params);
	}
}

void	move_right(t_params *params)
{
	double	x;
	double	y;
	double	sin_value;
	double	cos_value;

	sin_value = sin(params->player.direction + M_PI / 2) * MOVE_SPEED;
	cos_value = cos(params->player.direction + M_PI / 2) * MOVE_SPEED;
	y = (params->player.y + sin_value) - 0.0001;
	x = (params->player.x + cos_value) - 0.0001;
	if (params->map.map_data[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '0')
	{
		params->player.x += cos_value;
		params->player.y += sin_value;
		cast_rays(params);
	}
}
