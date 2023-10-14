/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:16:04 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:08:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	contains_newline(t_queue_char *q)
{
	struct s_queue_node_char	*tmp;

	tmp = q->front;
	while (tmp)
	{
		if (tmp->val == '\n')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*get_line(t_queue_char *q)
{
	int							i;
	char						*line;
	struct s_queue_node_char	*tmp;

	i = 0;
	tmp = q->front;
	while (tmp && tmp->val != '\n')
	{
		tmp = tmp->next;
		i++;
	}
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (q->front && q->front->val != '\n')
		line[i++] = dequeue_char(q);
	line[i++] = dequeue_char(q);
	line[i] = '\0';
	return (line);
}

char	*get_last_line(t_queue_char *q)
{
	int							i;
	char						*line;
	struct s_queue_node_char	*tmp;

	i = 0;
	tmp = q->front;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (q->front)
		line[i++] = dequeue_char(q);
	line[i] = '\0';
	return (line);
}

char	*handle_bytes(ssize_t bytes, t_queue_char *q, char *buffer, int *fd)
{
	ssize_t	i;

	if (bytes == -1)
	{
		free(buffer);
		return (NULL);
	}
	else if (bytes == 0)
	{
		free(buffer);
		if (q->front == NULL)
			return (NULL);
		else
			return (get_last_line(q));
	}
	else
	{
		i = 0;
		while (i < bytes)
			enqueue_char(q, buffer[i++]);
		free(buffer);
		return (get_next_line(*fd));
	}
}

char	*get_next_line(int fd)
{
	static t_queue_char	q;
	ssize_t				bytes;
	char				*buffer;
	static int			flag = 0;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (flag == 0)
	{
		init_queue_char(&q);
		flag = 1;
	}
	if (q.front && contains_newline(&q))
		return (get_line(&q));
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	return (handle_bytes(bytes, &q, buffer, &fd));
}
