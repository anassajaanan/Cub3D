/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:47:49 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/11 08:22:12 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	count_rows_in_queue(t_queue *queue)
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

static int	find_max_columns_in_queue(t_queue *queue)
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

static void	add_row_to_2d_array(char **map, t_queue *queue, int *index,
									int columns)
{
	int		i;
	char	*old_row;
	char	*new_row;
	int		old_row_len;

	i = 0;
	old_row = dequeue(queue);
	old_row_len = ft_strlen(old_row);
	if (old_row[old_row_len - 1] == '\n')
		old_row_len--;
	new_row = (char *)malloc(sizeof(char) * (columns));
	while (i < old_row_len)
	{
		new_row[i] = old_row[i];
		i++;
	}
	while (i < columns - 1)
		new_row[i++] = ' ';
	new_row[i] = '\0';
	map[*index] = new_row;
	(*index)++;
	ft_free((void **)&old_row);
}

void	convert_queue_to_2d_array(t_map *map, t_queue *queue)
{
	int		index;

	index = 0;
	map->rows = count_rows_in_queue(queue);
	map->cols = find_max_columns_in_queue(queue);
	map->map_data = (char **)malloc(sizeof(char *) * (map->rows + 1));
	while (queue->front)
		add_row_to_2d_array(map->map_data, queue, &index, map->cols);
	map->map_data[index] = NULL;
}
