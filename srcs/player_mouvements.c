/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:24:33 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 15:13:54 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_up(t_params *params)
{
	params->player.x += params->player.dx;
	params->player.y += params->player.dy;
	cast_rays(params);
}

void	move_down(t_params *params)
{
	params->player.x -= params->player.dx;
	params->player.y -= params->player.dy;
	cast_rays(params);
}

void	move_left(t_params *params)
{
	params->player.x -= cos(params->player.direction + M_PI / 2) * MOVE_SPEED;
	params->player.y -= sin(params->player.direction + M_PI / 2) * MOVE_SPEED;
	cast_rays(params);
}

void	move_right(t_params *params)
{
	params->player.x += cos(params->player.direction + M_PI / 2) * MOVE_SPEED;
	params->player.y += sin(params->player.direction + M_PI / 2) * MOVE_SPEED;
	cast_rays(params);
}
