/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 07:43:23 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/11 09:34:45 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf_fd(2, "Error\nWrong number of arguments\n");
		return (INVALID_ARG);
	}
	if (ft_strlen(argv[1]) < 5 || ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4,
			".cub", 4) != 0)
	{
		ft_printf_fd(2, "Error\nWrong file extension\n");
		return (INVALID_ARG);
	}
	return (SUCCESS);
}

int	parse_and_validate(int argc, char **argv, t_map_infos *map_infos,
		t_map *map)
{
	int	ret;

	if (validate_arguments(argc, argv) != SUCCESS)
		return (INVALID_ARG);
	ret = parse_map(argv[1], map_infos);
	if (ret == SUCCESS)
	{
		convert_queue_to_2d_array(map, &map_infos->queue);
		if (!is_valid_map(map))
			return (WRONG_MAP);
	}
	return (ret);
}

void	init_params(t_params *params)
{
	params->mlx = NULL;
	params->win = NULL;
	params->window_img.img = NULL;
	params->window_img.addr = NULL;
	
	params->map_infos.so_path = NULL;
	params->map_infos.no_path = NULL;
	params->map_infos.we_path = NULL;
	params->map_infos.ea_path = NULL;
	params->map_infos.queue.front = NULL;
	params->map_infos.queue.rear = NULL;
	params->map_infos.no_path_parsed = 0;
	params->map_infos.so_path_parsed = 0;
	params->map_infos.we_path_parsed = 0;
	params->map_infos.ea_path_parsed = 0;
	params->map_infos.floor_color_parsed = 0;
	params->map_infos.ceiling_color_parsed = 0;

	params->map.map_data = NULL;
	
	params->north_texture.img = NULL;
	params->north_texture.addr = NULL;
	params->south_texture.img = NULL;
	params->south_texture.addr = NULL;
	params->west_texture.img = NULL;
	params->west_texture.addr = NULL;
	params->east_texture.img = NULL;
	params->east_texture.addr = NULL;
}

int	main(int argc, char **argv)
{
	t_params	params;

	init_params(&params);
	if (parse_and_validate(argc, argv, &params.map_infos,
			&params.map) != SUCCESS)
	{
		free_and_cleanup(&params);
		return (1);
	}
	printf("The game started successfully\n");
	sleep(2);
	printf("The game finished successfully\n");
	free_and_cleanup(&params);
	return (0);
	
}
