/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 04:54:38 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/16 09:05:07 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

static int	has_valid_neighbors(t_map *map, int i, int j)
{
	if (map->map_data[i][j + 1] == ' '
		|| map->map_data[i][j - 1] == ' '
		|| map->map_data[i + 1][j] == ' '
		|| map->map_data[i - 1][j] == ' ')
		return (0);
	return (1);
}

static int	validate_map_element(t_map *map, int i, int j)
{
	char	c;

	c = map->map_data[i][j];
	if (i == 0 || i == map->rows - 1 || j == 0 || j == map->cols - 1)
	{
		if (c != '1' && c != ' ')
		{
			ft_printf_fd(2, "Error\nMap is not enclosed by \
walls at row %d, col %d\n", i + 1, j + 1);
			return (0);
		}
	}
	else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (!has_valid_neighbors(map, i, j))
		{
			ft_printf_fd(2, "Error\n");
			ft_printf_fd(2, "Invalid placement of '%c' at \
row %d, col %d\n", c, i + 1, j + 1);
			return (0);
		}
	}
	return (1);
}

static int	is_enclosed_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map_data[i])
	{
		j = 0;
		while (map->map_data[i][j])
		{
			if (!validate_map_element(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_valid_map(t_map *map)
{
	int	i;
	int	j;
	int	start_count;

	i = 0;
	j = 0;
	start_count = 0;
	while (map->map_data[i])
	{
		j = 0;
		while (map->map_data[i][j])
		{
			if (!is_valid_map_char(map->map_data[i][j]))
				return (ft_printf_fd(2, "Error\nInvalid character in map: {%c}\n",
						map->map_data[i][j]), 0);
			if (map->map_data[i][j] == 'N' || map->map_data[i][j] == 'S'
				|| map->map_data[i][j] == 'E' || map->map_data[i][j] == 'W')
				start_count++;
			j++;
		}
		i++;
	}
	if (start_count != 1)
		return (ft_printf_fd(2, "Error\nInvalid number of starting \
positions\n"), 0);
	return (is_enclosed_map(map));
}
