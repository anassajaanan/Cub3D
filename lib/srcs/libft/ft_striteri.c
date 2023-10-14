/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 07:56:14 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:08:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	unsigned int	len;

	if (!str || !f)
		return ;
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		f(i, &str[i]);
		i++;
	}
}
