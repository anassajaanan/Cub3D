/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 04:54:38 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/05 06:23:01 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_enclosed_map(t_map *map);

static int		is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

int	validate_map_characters(t_map *map)
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
			{
				ft_printf_fd(2, "Error\nInvalid character in map: %c\n", map->map_data[i][j]);
				return (0);
			}
			if (map->map_data[i][j] == 'N' || map->map_data[i][j] == 'S'
				|| map->map_data[i][j] == 'E' || map->map_data[i][j] == 'W')
				start_count++;
			j++;
		}
		i++;
	}
	if (start_count != 1)
	{
		ft_printf_fd(2, "Error\nInvalid number of starting positions\n");
		return (0);
	}
	return (is_enclosed_map(map));
}

int	is_enclosed_map(t_map *map)
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
			if (i == 0 || i == map->rows - 1 || j == 0 || j == map->cols - 1)
			{
				if (map->map_data[i][j] != '1' && map->map_data[i][j] != ' ')
				{
					ft_printf_fd(2, "Error\nMap is not enclosed 1\n");
					return (0);
				}
			}
			else if (map->map_data[i][j] == '0' || map->map_data[i][j] == 'N' || map->map_data[i][j] == 'S' || map->map_data[i][j] == 'E' || map->map_data[i][j] == 'W')
			{
				if (map->map_data[i][j + 1] == ' ' || map->map_data[i][j - 1] == ' ' || map->map_data[i + 1][j] == ' ' || map->map_data[i - 1][j] == ' ' || map->map_data[i + 1][j + 1] == ' ' || map->map_data[i + 1][j - 1] == ' ' || map->map_data[i - 1][j + 1] == ' ' || map->map_data[i - 1][j - 1] == ' ')
				{
					ft_printf_fd(2, "Error\nMap is not enclosed 2: row: %d, col: %d\n", i, j);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}