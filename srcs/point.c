/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:18:44 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 16:46:32 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_point	init_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

int	mlx_pixel_put_img(t_params *params, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = y * params->window_img.line_length
		+ x * params->window_img.bpp;
	if (pixel_index >= 0 && pixel_index < params->window_img.line_length
		* params->window_img.height)
		*(unsigned int *)(params->window_img.addr + pixel_index) = color;
	return (0);
}
