/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:56:11 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 15:13:49 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	normalize_direction(double *direction)
{
	if (*direction < 0)
		*direction += 2 * M_PI;
	if (*direction > 2 * M_PI)
		*direction -= 2 * M_PI;
}

void	look_left(t_params *params)
{
	params->player.direction -= ROTATE_SPEED;
	normalize_direction(&params->player.direction);
	params->player.dx = cos(params->player.direction) * MOVE_SPEED;
	params->player.dy = sin(params->player.direction) * MOVE_SPEED;
	cast_rays(params);
}

void	look_right(t_params *params)
{
	params->player.direction += ROTATE_SPEED;
	normalize_direction(&params->player.direction);
	params->player.dx = cos(params->player.direction) * MOVE_SPEED;
	params->player.dy = sin(params->player.direction) * MOVE_SPEED;
	cast_rays(params);
}
