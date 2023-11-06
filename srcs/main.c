/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 07:43:23 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 10:55:37 by aajaanan         ###   ########.fr       */
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
	if (ft_strlen(argv[1]) < 5 
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		ft_printf_fd(2, "Error\nWrong file extension\n");
		return (INVALID_ARG);
	}
	return (SUCCESS);
}

int	parse_and_validate(int argc, char **argv, t_map_infos *map_infos, t_map *map)
{
	int	ret;
	
	if (validate_arguments(argc, argv) != SUCCESS)
		return (INVALID_ARG);
	init_map_infos(map_infos);
	ret = parse_map(argv[1], map_infos);
	if (ret == SUCCESS)
	{
		convert_queue_to_2D_array(map, &map_infos->queue);
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
	int	red;
	int	green;
	int	blue;
	
	params->mlx = NULL;
	params->win = NULL;
	
	params->window_img.img = NULL;
	params->window_img.addr = NULL;
	red = params->map_infos.floor_color.red;
	green = params->map_infos.floor_color.green;
	blue = params->map_infos.floor_color.blue;
	params->floor_color = (red << 16) | (green << 8) | blue;
	red = params->map_infos.ceiling_color.red;
	green = params->map_infos.ceiling_color.green;
	blue = params->map_infos.ceiling_color.blue;
	params->ceiling_color = (red << 16) | (green << 8) | blue;
}

void	normalize_direction(double *direction)
{
	if (*direction < 0)
		*direction += 2 * M_PI;
	if (*direction > 2 * M_PI)
		*direction -= 2 * M_PI;
}

int	key_hook(int keycode, t_params *params)
{
	if (keycode == 53)
	{
		free_and_cleanup(params);
		exit(0);
	}
	else if (keycode == 123) // left arrow
	{
		params->player.direction -= ROTATE_SPEED;
		normalize_direction(&params->player.direction);
		params->player.dx = cos(params->player.direction) * MOVE_SPEED;
		params->player.dy = sin(params->player.direction) * MOVE_SPEED;
		cast_rays(params);
	}
	else if (keycode == 124) // right arrow
	{
		params->player.direction += ROTATE_SPEED;
		normalize_direction(&params->player.direction);
		params->player.dx = cos(params->player.direction) * MOVE_SPEED;
		params->player.dy = sin(params->player.direction) * MOVE_SPEED;
		cast_rays(params);
	}
	else if (keycode == 13) // W
	{
		params->player.x += params->player.dx;
		params->player.y += params->player.dy;
		cast_rays(params);
	}
	else if (keycode == 1) // S
	{
		params->player.x -= params->player.dx;
		params->player.y -= params->player.dy;
		cast_rays(params);
	}
	else if (keycode == 0) // A
	{
		params->player.x -= cos(params->player.direction + M_PI / 2) * MOVE_SPEED;
		params->player.y -= sin(params->player.direction + M_PI / 2) * MOVE_SPEED;
		cast_rays(params);
	}
	else if (keycode == 2) // D
	{
		params->player.x += cos(params->player.direction + M_PI / 2) * MOVE_SPEED;
		params->player.y += sin(params->player.direction + M_PI / 2) * MOVE_SPEED;
		cast_rays(params);
	}
	return (0);
}

int	update_window(t_params *params)
{
	mlx_put_image_to_window(params->mlx, params->win, params->window_img.img, 0, 0);
	return (0);

}

int main(int argc, char **argv)
{
	t_params	params;
	

	if (parse_and_validate(argc, argv, &params.map_infos, &params.map) != SUCCESS)
		return (1);
	init_params(&params);
	params.mlx = mlx_init();
	params.win = mlx_new_window(params.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (init_window_image(&params) != SUCCESS)
		return (1);
	init_player(&params);
	
	
	
	mlx_key_hook(params.win, key_hook, &params);
	mlx_loop_hook(params.mlx, update_window, &params);
	mlx_loop(params.mlx);
}