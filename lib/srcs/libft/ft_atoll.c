/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:19:56 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:08:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	check_overflow(long long num, int sign, int digit)
{
	if (num > LONG_MAX / 10 || (num == LONG_MAX / 10 && digit > LLONG_MAX % 10))
	{
		if (sign == 1 || (sign == -1 && (digit > 8)))
			return (1);
	}
	return (0);
}

long long	ft_atoll(const char *str, int *over_under_flow)
{
	int			i;
	int			sign;
	long long	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (check_overflow(num, sign, str[i] - '0'))
			return (*over_under_flow = 1, 0);
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (*over_under_flow = 0, num * sign);
}
