/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:56:35 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:08:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	init_queue_char(t_queue_char *q)
{
	q->front = NULL;
	q->rear = NULL;
}

void	enqueue_char(t_queue_char *q, char c)
{
	struct s_queue_node_char	*new_node;

	new_node = (struct s_queue_node_char *)malloc(sizeof(
				struct s_queue_node_char));
	if (!new_node)
		return ;
	new_node->val = c;
	new_node->next = NULL;
	if (q->front == NULL)
	{
		q->front = new_node;
		q->rear = new_node;
	}
	else
	{
		q->rear->next = new_node;
		q->rear = new_node;
	}
}

char	dequeue_char(t_queue_char *q)
{
	char						value;
	struct s_queue_node_char	*tmp;

	tmp = q->front;
	q->front = q->front->next;
	value = tmp->val;
	free(tmp);
	return (value);
}

void	enqueue_str(t_queue_char *q, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		enqueue_char(q, str[i]);
		i++;
	}
}

char	*queue_char_to_str(t_queue_char *q)
{
	struct s_queue_node_char	*tmp;
	char						*str;
	int							i;

	i = 0;
	tmp = q->front;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (q->front)
		str[i++] = dequeue_char(q);
	str[i] = '\0';
	return (str);
}
