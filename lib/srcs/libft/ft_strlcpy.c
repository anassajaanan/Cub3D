/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:13:00 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:08:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;	
	size_t	j;

	i = 0;
	j = ft_strlen(src);
	if (size != 0)
	{
		while (i < size - 1 && i < j)
		{
			dest[i] = ((char *)src)[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (j);
}
