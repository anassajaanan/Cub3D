/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 03:43:28 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/16 08:59:56 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_player_pos(t_params *params, int i, int j)
{
	params->player.x = j * TILE_SIZE + 20;
	params->player.y = i * TILE_SIZE + 20;
	if (params->map.map_data[i][j] == 'N')
		params->player.direction = 3 * M_PI / 2;
	else if (params->map.map_data[i][j] == 'S')
		params->player.direction = M_PI / 2;
	else if (params->map.map_data[i][j] == 'E')
		params->player.direction = 0;
	else if (params->map.map_data[i][j] == 'W')
		params->player.direction = M_PI;
	params->player.dx = cos(params->player.direction) * MOVE_SPEED;
	params->player.dy = sin(params->player.direction) * MOVE_SPEED;
	params->player.fov = M_PI / 3;
}

void	init_player(t_params *params)
{
	int	i;
	int	j;

	i = 0;
	while (i < params->map.rows)
	{
		j = 0;
		while (j < params->map.cols)
		{
			if (params->map.map_data[i][j] == 'N' 
				|| params->map.map_data[i][j] == 'S'
				|| params->map.map_data[i][j] == 'E'
				|| params->map.map_data[i][j] == 'W')
			{
				init_player_pos(params, i, j);
				params->map.map_data[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_colors(t_params *params)
{
	int	red;
	int	green;
	int	blue;

	red = params->map_infos.floor_color.red;
	green = params->map_infos.floor_color.green;
	blue = params->map_infos.floor_color.blue;
	params->floor_color = (red << 16) | (green << 8) | blue;
	red = params->map_infos.ceiling_color.red;
	green = params->map_infos.ceiling_color.green;
	blue = params->map_infos.ceiling_color.blue;
	params->ceiling_color = (red << 16) | (green << 8) | blue;
}
