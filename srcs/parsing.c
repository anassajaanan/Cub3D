/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 07:43:06 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/11 06:54:12 by aajaanan         ###   ########.fr       */
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

int	count_commas(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
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
	// count the number of commas in the color string
	if (count_commas(array[1]) != 2)
	{
		ft_printf_fd(STDERR_FILENO, "Error\n");
		ft_printf_fd(STDERR_FILENO, "Invalid color format. Please use three \
comma-separated digits for the color components (e.g., 'R,G,B').\n");
		return (WRONG_MAP);
	}
	colors = ft_split(array[1], ',');
	if (validate_colors(color, colors) == WRONG_MAP)
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
		ft_free((void **)&line);
		line = get_next_line(fd);
	}
	while (line && !is_empty_line(line))
	{
		enqueue(q, line);
		line = get_next_line(fd);
	}
	ft_free((void **)&line);
}

static int	parse_line(t_map_infos *map_infos, char *map_line)
{
	char	**array;

	array = ft_split(map_line, ' ');
	if (startswith(array, "NO"))
	{
		if (map_infos->no_path_parsed)
		{
			ft_printf_fd(STDERR_FILENO, "Error\n");
			ft_printf_fd(STDERR_FILENO, "Duplicate NO texture path.\n");
			return (free_split_array(array), WRONG_MAP);
		}
		else
		{
			if (parse_texture_line(map_infos, array) != SUCCESS)
				return (free_split_array(array), WRONG_MAP);
			map_infos->no_path_parsed = 1;
		}
	}
	else if (startswith(array, "SO"))
	{
		if (map_infos->so_path_parsed)
		{
			ft_printf_fd(STDERR_FILENO, "Error\n");
			ft_printf_fd(STDERR_FILENO, "Duplicate SO texture path.\n");
			return (free_split_array(array), WRONG_MAP);
		}
		else
		{
			if (parse_texture_line(map_infos, array) != SUCCESS)
				return (free_split_array(array), WRONG_MAP);
			map_infos->so_path_parsed = 1;
		}
	}
	else if (startswith(array, "WE"))
	{
		if (map_infos->we_path_parsed)
		{
			ft_printf_fd(STDERR_FILENO, "Error\n");
			ft_printf_fd(STDERR_FILENO, "Duplicate WE texture path.\n");
			return (free_split_array(array), WRONG_MAP);
		}
		else
		{
			if (parse_texture_line(map_infos, array) != SUCCESS)
				return (free_split_array(array), WRONG_MAP);
			map_infos->we_path_parsed = 1;
		}
	}
	else if (startswith(array, "EA"))
	{
		if (map_infos->ea_path_parsed)
		{
			ft_printf_fd(STDERR_FILENO, "Error\n");
			ft_printf_fd(STDERR_FILENO, "Duplicate EA texture path.\n");
			return (free_split_array(array), WRONG_MAP);
		}
		else
		{
			if (parse_texture_line(map_infos, array) != SUCCESS)
				return (free_split_array(array), WRONG_MAP);
			map_infos->ea_path_parsed = 1;
		}
	}
	else if (startswith(array, "F"))
	{
		if (map_infos->floor_color_parsed)
		{
			ft_printf_fd(STDERR_FILENO, "Error\n");
			ft_printf_fd(STDERR_FILENO, "Duplicate floor color.\n");
			return (free_split_array(array), WRONG_MAP);
		}
		else
		{
			if (parse_color_line(map_infos, array) != SUCCESS)
				return (free_split_array(array), WRONG_MAP);
			map_infos->floor_color_parsed = 1;
		}
	}
	else if (startswith(array, "C"))
	{
		if (map_infos->ceiling_color_parsed)
		{
			ft_printf_fd(STDERR_FILENO, "Error\n");
			ft_printf_fd(STDERR_FILENO, "Duplicate ceiling color.\n");
			return (free_split_array(array), WRONG_MAP);
		}
		else
		{
			if (parse_color_line(map_infos, array) != SUCCESS)
				return (free_split_array(array), WRONG_MAP);
			map_infos->ceiling_color_parsed = 1;
		}
	}
	else
	{
		ft_printf_fd(2, "Error\n");
		ft_printf_fd(2, "This line is invalid: {%s}\n", map_line);
		ft_printf_fd(2, "Please provide a valid line.\n");
		return (free_split_array(array), WRONG_MAP);
	}
	return (free_split_array(array), SUCCESS);
}

// int	parse_map(char *file_name, t_map_infos *map_infos)
// {
// 	int		fd;
// 	char	*line;
// 	char	*map_line;

// 	fd = open_map_file(file_name);
// 	if (fd == -1)
// 		return (ft_printf_fd(2, "Error\nCould not open file\n"), OPEN_ERR);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		map_line = ft_strtrim(line, " \t\v\f\r\n");
// 		ft_free((void **)&line);
// 		if (*map_line && parse_line(map_infos, map_line) != SUCCESS)
// 			return (ft_free((void **)&map_line), close(fd), WRONG_MAP);
// 		ft_free((void **)&map_line);
// 		if (map_infos->parsed_texture_count == 4 
// 			&& map_infos->parsed_color_count == 2)
// 			break ;
// 		line = get_next_line(fd);
// 	}
// 	line = get_next_line(fd);
// 	if (line == NULL)
// 		return (close(fd), ft_printf_fd(2, "Error\n"), ft_printf_fd(2, "
// Invalid map file. Please provide a valid map file.\n"), WRONG_MAP);
// 	ft_free((void **)&line);
// 	parse_map_to_queue(fd, &map_infos->queue);
// 	return (close(fd), SUCCESS);
// }

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
		if (map_infos->no_path_parsed == 1 && map_infos->so_path_parsed == 1
			&& map_infos->we_path_parsed == 1 && map_infos->ea_path_parsed == 1
			&& map_infos->floor_color_parsed == 1 && map_infos->ceiling_color_parsed == 1)
			break ;
		line = get_next_line(fd);
	}
	if (map_infos->no_path_parsed != 1 || map_infos->so_path_parsed != 1
		|| map_infos->we_path_parsed != 1 || map_infos->ea_path_parsed != 1
		|| map_infos->floor_color_parsed != 1 || map_infos->ceiling_color_parsed != 1)
	{
		ft_printf_fd(2, "Error\n");
		ft_printf_fd(2, "Invalid map file. The following elements are missing:\n");
		
		if (map_infos->no_path_parsed != 1)
			ft_printf_fd(2, "  - NO texture path\n");
		if (map_infos->so_path_parsed != 1)
			ft_printf_fd(2, "  - SO texture path\n");
		if (map_infos->we_path_parsed != 1)
			ft_printf_fd(2, "  - WE texture path\n");
		if (map_infos->ea_path_parsed != 1)
			ft_printf_fd(2, "  - EA texture path\n");
		if (map_infos->floor_color_parsed != 1)
			ft_printf_fd(2, "  - Floor color\n");
		if (map_infos->ceiling_color_parsed != 1)
			ft_printf_fd(2, "  - Ceiling color\n");
		return (close(fd), WRONG_MAP);
	}
	parse_map_to_queue(fd, &map_infos->queue);
	return (close(fd), SUCCESS);
}
