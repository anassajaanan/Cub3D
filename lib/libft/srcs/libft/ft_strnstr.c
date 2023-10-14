/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:41:06 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:08:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strnstr(const char *str, const char *sub_str, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	sub_len;

	i = 0;
	sub_len = ft_strlen(sub_str);
	if (sub_len == 0)
		return ((char *)str);
	if (len == 0)
		return (NULL);
	while (str[i] && i <= len - sub_len)
	{
		j = 0;
		while (str[i + j] && sub_str[j] && str[i + j] == sub_str[j])
			j++;
		if (sub_str[j] == '\0')
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
