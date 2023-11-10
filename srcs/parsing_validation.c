/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:12:58 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/10 14:39:37 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	are_valid_colors(char **colors)
{
	int	i;

	i = 0;
	while (colors[i])
	{
		if (!is_numeric(colors[i]))
			return (0);
		i++;
	}
	return (i == 3);
}

static int	is_valid_color(t_color *color)
{
	if (color->red < 0 || color->red > 255)
		return (0);
	if (color->green < 0 || color->green > 255)
		return (0);
	if (color->blue < 0 || color->blue > 255)
		return (0);
	return (1);
}

int	validate_colors(t_color *color, char **colors)
{
	if (!are_valid_colors(colors))
	{
		ft_printf_fd(STDERR_FILENO, "Error\n");
		ft_printf_fd(STDERR_FILENO, "Invalid color format. Please use three \
comma-separated digits for the color components (e.g., 'R,G,B').\n");
		return (WRONG_MAP);
	}
	color->red = ft_atoi(colors[0]);
	color->green = ft_atoi(colors[1]);
	color->blue = ft_atoi(colors[2]);
	if (!is_valid_color(color))
	{
		ft_printf_fd(STDERR_FILENO, "Error\n");
		ft_printf_fd(STDERR_FILENO, "Color components must be between 0 \
and 255.\n");
		return (WRONG_MAP);
	}
	return (SUCCESS);
}

int	is_valid_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}
