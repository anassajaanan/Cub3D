/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 07:16:00 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:08:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t		i;
	size_t		j;
	size_t		len;
	char		*new_str;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen((char *)s1))
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen((char *)s2))
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}
