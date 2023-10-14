/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 07:28:02 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:08:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	get_num_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		i = 1;
		n *= -1;
	}
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		stop;
	int		len;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	stop = 0;
	len = get_num_len(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[0] = '-';
	res[len] = '\0';
	if (n < 0)
	{
		n *= -1;
		stop = 1;
	}
	while (len > stop)
	{
		res[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (res);
}
