/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 03:43:28 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 10:12:53 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_map_infos(t_map_infos *map_infos)
{
	map_infos->so_path = NULL;
	map_infos->no_path = NULL;
	map_infos->we_path = NULL;
	map_infos->ea_path = NULL;
	map_infos->parsed_color_count = 0;
	map_infos->parsed_texture_count = 0;
}

int	init_window_image(t_params *params)
{
	params->window_img.height = WINDOW_HEIGHT;
	params->window_img.width = WINDOW_WIDTH;
	params->window_img.img = mlx_new_image(params->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!params->window_img.img)
	{
		free_and_cleanup(params);
		return (IMG_FAIL);
	}
	params->window_img.addr = mlx_get_data_addr(params->window_img.img,
			&params->window_img.bits_per_pixel, &params->window_img.line_length,
			&params->window_img.endian);
	if (!params->window_img.addr)
	{
		free_and_cleanup(params);
		return (IMG_FAIL);
	}
	params->window_img.bpp = params->window_img.bits_per_pixel / 8;
	return (SUCCESS);
}

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
