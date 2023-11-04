/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 07:43:23 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/04 12:33:30 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <unistd.h>

void	parse_map_to_queue(int fd, t_queue *q);

int startswith(char **array, char *str)
{
	if (ft_strcmp(array[0], str) == 0)
		return (1);
	return (0);
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

int	array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	parse_texture_line(t_map_infos *map_infos, char **array)
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
		map_infos->north_texture.path = ft_strdup(array[1]);
	else if (ft_strcmp(array[0], "SO") == 0)
		map_infos->south_texture.path = ft_strdup(array[1]);
	else if (ft_strcmp(array[0], "WE") == 0)
		map_infos->west_texture.path = ft_strdup(array[1]);
	else if (ft_strcmp(array[0], "EA") == 0)
		map_infos->east_texture.path = ft_strdup(array[1]);
	return (SUCCESS);
}


int	is_valid_colors(char **colors)
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

int	is_valid_color(t_color *color)
{
	if (color->red < 0 || color->red > 255)
		return (0);
	if (color->green < 0 || color->green > 255)
		return (0);
	if (color->blue < 0 || color->blue > 255)
		return (0);
	return (1);
}

int	validate_colors(t_map_infos *map_infos, t_color *color, char **colors)
{
	if (!is_valid_colors(colors))
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

int	parse_color_line(t_map_infos *map_infos, char **array)
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

int open_map_file(char *file_name)
{
    int fd = open(file_name, O_RDONLY);
    if (fd == -1)
        return -1;
    return fd;
}


int	parse_line(t_map_infos *map_infos, char *map_line)
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
		ft_printf_fd(STDERR_FILENO, "Invalid line in the map. Each line in the map \
should start with a texture or a color definition.\n");
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
		return (OPEN_ERR);
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
	parse_map_to_queue(fd, &map_infos->map);
	printf("Correct Map\n");
	close(fd);
	return (SUCCESS);
}

void	init_map_infos(t_map_infos *map_infos)
{
	map_infos->south_texture.path = NULL;
	map_infos->north_texture.path = NULL;
	map_infos->west_texture.path = NULL;
	map_infos->east_texture.path = NULL;

	map_infos->parsed_color_count = 0;
	map_infos->parsed_texture_count = 0;
}

void	free_map_infos(t_map_infos *map_infos)
{
	ft_free(map_infos->north_texture.path);
	ft_free(map_infos->south_texture.path);
	ft_free(map_infos->west_texture.path);
	ft_free(map_infos->east_texture.path);

	free_queue(&map_infos->map);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\v' && line[i] != '\f' && line[i] != '\r' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	parse_map_to_queue(int fd, t_queue *q)
{
	char	*line;
	
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

int main()
{
	t_map_infos	map_infos;
	int ret;
	
	char	map[] = "./map.cub";

	init_map_infos(&map_infos);
	init_queue(&map_infos.map);
	ret = parse_map(map, &map_infos);

	if (ret == SUCCESS)
	{
		printf("NO: %s\n", map_infos.north_texture.path);
		printf("SO: %s\n", map_infos.south_texture.path);
		printf("WE: %s\n", map_infos.west_texture.path);
		printf("EA: %s\n", map_infos.east_texture.path);
		printf("F: %d, %d, %d\n", map_infos.floor_color.red, map_infos.floor_color.green, map_infos.floor_color.blue);
		printf("C: %d, %d, %d\n", map_infos.ceiling_color.red, map_infos.ceiling_color.green, map_infos.ceiling_color.blue);
		printf("Map:\n");
		t_queue_node	*tmp = map_infos.map.front;
		while (tmp)
		{
			printf("%s", tmp->val);
			tmp = tmp->next;
		}
	}


	free_map_infos(&map_infos);
	return (ret);
	
}