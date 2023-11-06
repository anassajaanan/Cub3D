/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 03:43:28 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 15:24:50 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



static void	init_player_pos(t_params *params, int i, int j)
{
	params->player.x = j * TILE_SIZE + TILE_SIZE / 2;
	params->player.y = i * TILE_SIZE + TILE_SIZE / 2;
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
				return ;
			}
			j++;
		}
		i++;
	}
}
