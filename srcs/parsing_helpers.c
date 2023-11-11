/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 07:43:23 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/11 07:03:27 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	startswith(char **array, char *str)
{
	if (ft_strcmp(array[0], str) == 0)
		return (1);
	return (0);
}

int	array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\v'
			&& line[i] != '\f' && line[i] != '\r' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	open_map_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (*str == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
