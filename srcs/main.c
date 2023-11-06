/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 07:43:23 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/06 04:04:00 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <unistd.h>




void	free_map_infos(t_map_infos *map_infos)
{
	ft_free(map_infos->north_texture.path);
	ft_free(map_infos->south_texture.path);
	ft_free(map_infos->west_texture.path);
	ft_free(map_infos->east_texture.path);

	free_queue(&map_infos->queue);
}

int	count_rows_in_queue(t_queue *queue)
{
	int				i;
	t_queue_node	*tmp;

	i = 0;
	tmp = queue->front;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	find_max_columns_in_queue(t_queue *queue)
{
	int				max;
	int				len;
	t_queue_node	*tmp;

	max = INT_MIN;
	tmp = queue->front;
	while (tmp)
	{
		len = ft_strlen(tmp->val);
		if (len > max)
			max = len;
		tmp = tmp->next;
	}
	return (max);
}

void	add_row_to_2D_array(char **map, t_queue *queue, int *index, int columns)
{
	int		i;
	char	*old_row;
	char	*new_row;
	int		old_row_len;

	i = 0;
	old_row = dequeue(queue);
	old_row_len = ft_strlen(old_row);
	new_row = (char *)malloc(sizeof(char) * (columns));
	while (i < old_row_len - 1)
	{
		if (old_row[i] == ' ')
			new_row[i] = ' ';
		else
			new_row[i] = old_row[i];
		i++;
	}
	while (i < columns - 1)
		new_row[i++] = ' ';
	new_row[i] = '\0';
	map[*index] = new_row;
	(*index)++;
	ft_free(old_row);
}

void	convert_queue_to_2D_array(t_map *map, t_queue *queue)
{
	int		index;

	index = 0;
	map->rows = count_rows_in_queue(queue);
	map->cols = find_max_columns_in_queue(queue);
	map->map_data = (char **)malloc(sizeof(char *) * (map->rows + 1));
	while (queue->front)
		add_row_to_2D_array(map->map_data, queue, &index, map->cols);
	map->map_data[index] = NULL;
}

void	free_2D_array(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_free(map[i]);
		i++;
	}
	ft_free(map);
}

int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf_fd(2, "Error\nWrong number of arguments\n");
		return (INVALID_ARG);
	}
	if (ft_strlen(argv[1]) < 5 
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		ft_printf_fd(2, "Error\nWrong file extension\n");
		return (INVALID_ARG);
	}
	return (SUCCESS);
}

int	parse_and_validate(int argc, char **argv, t_map_infos *map_infos, t_map *map)
{
	int	ret;
	
	if (validate_arguments(argc, argv) != SUCCESS)
		return (INVALID_ARG);
	init_map_infos(map_infos);
	ret = parse_map(argv[1], map_infos);
	if (ret == SUCCESS)
	{
		convert_queue_to_2D_array(map, &map_infos->queue);
		if (!is_valid_map(map))
		{
			free_2D_array(map->map_data);
			free_map_infos(map_infos);
			return (WRONG_MAP);
		}
	}
	return (ret);
}

int main(int argc, char **argv)
{
	t_map_infos	map_infos;
	t_map		map;
	

	if (parse_and_validate(argc, argv, &map_infos, &map) != SUCCESS)
		return (1);
	

	free_2D_array(map.map_data);
	free_map_infos(&map_infos);
}