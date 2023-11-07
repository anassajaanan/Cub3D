/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 07:43:06 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/07 18:00:18 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	parse_texture_line(t_map_infos *map_infos, char **array)
{
	if (array_size(array) != 2)
	{
		ft_printf_fd(STDERR_FILENO, "Error\n");
		ft_printf_fd(STDERR_FILENO, "Invalid texture line format. Please provide \
only the texture identifier and the path.\n");
		return (WRONG_MAP);
	}
	if (!is_valid_texture_path(array[1]))
	{
		ft_printf_fd(STDERR_FILENO, "Error\n");
		ft_printf_fd(STDERR_FILENO, "Invalid or non-existent texture path. Please provide \
a valid and accessible file path for the texture.\n");
		return (WRONG_MAP);
	}
	if (ft_strcmp(array[0], "NO") == 0)
		map_infos->no_path = ft_strdup(array[1]);
	else if (ft_strcmp(array[0], "SO") == 0)
		map_infos->so_path = ft_strdup(array[1]);
	else if (ft_strcmp(array[0], "WE") == 0)
		map_infos->we_path = ft_strdup(array[1]);
	else if (ft_strcmp(array[0], "EA") == 0)
		map_infos->ea_path = ft_strdup(array[1]);
	return (SUCCESS);
}

static int	parse_color_line(t_map_infos *map_infos, char **array)
{
	char	**colors;
	t_color	*color;

	if (array_size(array) != 2)
		return (ft_printf_fd(STDERR_FILENO, "Error\n"), \
		ft_printf_fd(STDERR_FILENO, "Invalid color line format. Please provide \
only the color identifier and the color components.\n"), WRONG_MAP);
	if (ft_strcmp(array[0], "F") == 0)
		color = &map_infos->floor_color;
	else if (ft_strcmp(array[0], "C") == 0)
		color = &map_infos->ceiling_color;
	if (!ft_isdigit(array[1][0]) 
		|| !ft_isdigit(array[1][ft_strlen(array[1]) - 1]))
	{
		ft_printf_fd(STDERR_FILENO, "Error\n");
		ft_printf_fd(STDERR_FILENO, "Invalid color format. Please use three \
comma-separated digits for the color components (e.g., 'R,G,B').\n");
		return (WRONG_MAP);
	}
	colors = ft_split(array[1], ',');
	if (validate_colors(map_infos, color, colors) == WRONG_MAP)
		return (free_split_array(colors), WRONG_MAP);
	free_split_array(colors);
	return (SUCCESS);
}

static void	parse_map_to_queue(int fd, t_queue *q)
{
	char	*line;

	init_queue(q);
	line = get_next_line(fd);
	while (line && is_empty_line(line))
	{
		ft_free(line);
		line = get_next_line(fd);
	}
	while (line && !is_empty_line(line))
	{
		enqueue(q, line);
		line = get_next_line(fd);
	}
	ft_free(line);
}

static int	parse_line(t_map_infos *map_infos, char *map_line)
{
	char	**array;

	array = ft_split(map_line, ' ');
	if (startswith(array, "NO") || startswith(array, "SO") 
		|| startswith(array, "WE") || startswith(array, "EA"))
	{
		if (parse_texture_line(map_infos, array) != SUCCESS)
			return (free_split_array(array), WRONG_MAP);
		map_infos->parsed_texture_count++;
	}
	else if (startswith(array, "F") || startswith(array, "C"))
	{
		if (parse_color_line(map_infos, array) != SUCCESS)
			return (free_split_array(array), WRONG_MAP);
		map_infos->parsed_color_count++;
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "Error\n");
		ft_printf_fd(STDERR_FILENO, "Invalid line in the map.\n");
		return (free_split_array(array), WRONG_MAP);
	}
	return (free_split_array(array), SUCCESS);
}

int	parse_map(char *file_name, t_map_infos *map_infos)
{
	int		fd;
	char	*line;
	char	*map_line;

	fd = open_map_file(file_name);
	if (fd == -1)
		return (ft_printf_fd(2, "Error\nCould not open file\n"), OPEN_ERR);
	line = get_next_line(fd);
	while (line)
	{
		map_line = ft_strtrim(line, " \t\v\f\r\n");
		ft_free(line);
		if (*map_line && parse_line(map_infos, map_line) != SUCCESS)
			return (ft_free(map_line), close(fd), WRONG_MAP);
		ft_free(map_line);
		if (map_infos->parsed_texture_count == 4 
			&& map_infos->parsed_color_count == 2)
			break ;
		line = get_next_line(fd);
	}
	if (line == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "Error\n");
		ft_printf_fd(STDERR_FILENO, "Invalid map file. Please provide a valid map file.\n");
		return (close(fd), WRONG_MAP);
	}
	parse_map_to_queue(fd, &map_infos->queue);
	close(fd);
	return (SUCCESS);
}
