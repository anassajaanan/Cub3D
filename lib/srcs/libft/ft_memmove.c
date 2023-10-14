/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:14:14 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:08:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	if (dest == NULL && src == NULL)
		return (NULL);
	if (src > dest)
	{
		ft_memcpy(dest, src, len);
	}
	else
	{
		while (len > 0)
		{
			((unsigned char *)dest)[len - 1] = ((unsigned char *)src)[len - 1];
			len--;
		}
	}
	return (dest);
}
