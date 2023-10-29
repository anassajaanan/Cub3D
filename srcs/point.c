/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:18:44 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/29 09:23:06 by aajaanan         ###   ########.fr       */
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

int	mlx_pixel_put_img(void *mlx_ptr, t_img *img_ptr, int x, int y, int color)
{
	int	pixel_index;

	pixel_index = y * img_ptr->size_line + x * img_ptr->bpp;
	if (pixel_index >= 0 && pixel_index < img_ptr->size_line * img_ptr->height)
		*(unsigned int *)(img_ptr->addr + pixel_index) = color;
	return (0);
}