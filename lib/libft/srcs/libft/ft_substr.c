/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 07:12:40 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:08:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	j;

	if (!str)
		return (0);
	if (start >= ft_strlen(str))
		return (ft_strdup(""));
	if (len > ft_strlen(str))
		len = ft_strlen(str);
	sub_str = malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		return (0);
	i = start;
	j = 0;
	while (str[i] && j < len)
		sub_str[j++] = str[i++];
	sub_str[j] = '\0';
	return (sub_str);
}
