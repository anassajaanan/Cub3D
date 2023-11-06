/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:29:35 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 16:40:57 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	init_image(t_params *params, char *image_path, t_img *image)
{
	image->img = mlx_xpm_file_to_image(params->mlx, image_path, &image->width,
			&image->height);
	if (!image->img)
	{
		ft_printf_fd(2, "Error\nFailed to load texture\n");
		free_and_cleanup(params);
		return (IMG_FAIL);
	}
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	if (!image->addr)
	{
		ft_printf_fd(2, "Error\nFailed to load texture\n");
		free_and_cleanup(params);
		return (IMG_FAIL);
	}
	image->bpp = image->bits_per_pixel / 8;
	return (SUCCESS);
}

static int	init_textures(t_params *params)
{
	if (init_image(params, params->map_infos.no_path,
			&params->north_texture) != SUCCESS)
		return (IMG_FAIL);
	if (init_image(params, params->map_infos.so_path,
			&params->south_texture) != SUCCESS)
		return (IMG_FAIL);
	if (init_image(params, params->map_infos.we_path,
			&params->west_texture) != SUCCESS)
		return (IMG_FAIL);
	if (init_image(params, params->map_infos.ea_path,
			&params->east_texture) != SUCCESS)
		return (IMG_FAIL);
	return (SUCCESS);
}

static int	init_window_image(t_params *params)
{
	params->window_img.height = WINDOW_HEIGHT;
	params->window_img.width = WINDOW_WIDTH;
	params->window_img.img = mlx_new_image(params->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
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

int	init_images(t_params *params)
{
	if (init_window_image(params) != SUCCESS
		|| init_textures(params) != SUCCESS)
		return (IMG_FAIL);
	return (SUCCESS);
}
