/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 07:43:06 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/16 10:13:01 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <unistd.h>

static void	parse_map_to_queue(int fd, t_queue *q)
{
	char	*line;

	init_queue(q);
	line = get_next_line(fd);
	while (line && is_empty_line(line))
	{
		ft_free((void **)&line);
		line = get_next_line(fd);
	}
	while (line && !is_empty_line(line))
	{
		enqueue(q, ft_strtrim(line, "\n"));
		ft_free((void **)&line);
		line = get_next_line(fd);
	}
	ft_free((void **)&line);
}

static int	parse_line(t_map_infos *map_infos, char *map_line)
{
	char	**array;

	array = ft_split(map_line, ' ');
	if (startswith(array, "NO"))
		return (handle_texture_line(map_infos, &array,
				&map_infos->no_path_parsed, "NO"));
	else if (startswith(array, "SO"))
		return (handle_texture_line(map_infos, &array,
				&map_infos->so_path_parsed, "SO"));
	else if (startswith(array, "WE"))
		return (handle_texture_line(map_infos, &array,
				&map_infos->we_path_parsed, "WE"));
	else if (startswith(array, "EA"))
		return (handle_texture_line(map_infos, &array,
				&map_infos->ea_path_parsed, "EA"));
	else if (startswith(array, "F"))
		return (handle_color_line(map_infos, &array,
				&map_infos->floor_color_parsed, "floor"));
	else if (startswith(array, "C"))
		return (handle_color_line(map_infos, &array,
				&map_infos->ceiling_color_parsed, "ceiling"));
	else
		return (handle_invalid_line(&array, map_line));
}

int	all_elements_parsed(t_map_infos *map_infos)
{
	if (map_infos->no_path_parsed == 1 && map_infos->so_path_parsed == 1
		&& map_infos->we_path_parsed == 1 && map_infos->ea_path_parsed == 1
		&& map_infos->floor_color_parsed == 1
		&& map_infos->ceiling_color_parsed == 1)
		return (1);
	return (0);
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
		ft_free((void **)&line);
		if (*map_line && parse_line(map_infos, map_line) != SUCCESS)
			return (ft_free((void **)&map_line), close(fd), WRONG_MAP);
		ft_free((void **)&map_line);
		if (all_elements_parsed(map_infos))
			break ;
		line = get_next_line(fd);
	}
	if (!all_elements_parsed(map_infos))
		return (close(fd), print_missing_elements_error(map_infos));
	parse_map_to_queue(fd, &map_infos->queue);
	return (close(fd), SUCCESS);
}
