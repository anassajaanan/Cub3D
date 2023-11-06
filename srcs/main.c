/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 07:43:23 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 16:32:58 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>
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
		{
			free_2D_array(map->map_data);
			free_map_infos(map_infos);
			return (WRONG_MAP);
		}
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
	params->map_infos.parsed_color_count = 0;
	params->map_infos.parsed_texture_count = 0;
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

int	key_hook(int keycode, t_params *params)
{
	if (keycode == 53)
	{
		free_and_cleanup(params);
		exit(0);
	}
	else if (keycode == 123)
		look_left(params);
	else if (keycode == 124)
		look_right(params);
	else if (keycode == 13)
		move_up(params);
	else if (keycode == 1)
		move_down(params);
	else if (keycode == 0)
		move_left(params);
	else if (keycode == 2)
		move_right(params);
	return (0);
}

int	update_window(t_params *params)
{
	mlx_put_image_to_window(params->mlx, params->win, params->window_img.img, 0,
		0);
	return (0);
}



int	main(int argc, char **argv)
{
	t_params	params;

	init_params(&params);
	if (parse_and_validate(argc, argv, &params.map_infos,
			&params.map) != SUCCESS)
		return (1);
	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"cub3d");
	if (init_images(&params) != SUCCESS)
		return (1);
	init_player(&params);
	init_colors(&params);
	cast_rays(&params);
	mlx_key_hook(params.win, key_hook, &params);
	mlx_loop_hook(params.mlx, update_window, &params);
	mlx_loop(params.mlx);
}
