/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:06:46 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/10 12:07:29 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	{
		move_up(params);
	}
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

int	close_window(t_params *params)
{
	free_and_cleanup(params);
	exit(0);
}
