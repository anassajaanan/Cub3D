/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 20:04:31 by aajaanan          #+#    #+#             */
/*   Updated: 2023/11/04 11:51:24 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	skip_whitespace_and_sign(char *str, int *i, int *sign)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'
			|| str[*i] == '\v' || str[*i] == '\f' || str[*i] == '\r'))
		(*i)++;
	if (str[*i] && (str[*i] == '+' || str[*i] == '-'))
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

static int	handle_overflow(int sign)
{
	if (sign == 1)
		return (INT_MAX);
	else
		return (INT_MIN);
}

int	ft_atoi(char *str)
{
	int			i;
	int			sign;
	int			digit;
	long long	num;

	i = 0;
	sign = 1;
	num = 0;
	skip_whitespace_and_sign(str, &i, &sign);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		digit = str[i] - '0';
		if (num > LONG_MAX / 10 || (num == LONG_MAX / 10 && digit > 7))
		{
			if (sign == 1)
				return (INT_MAX);
			else if (sign == -1 && (digit > 8))
				return (INT_MIN);
		}
		num = (num * 10) + digit;
		i++;
	}
	if (num > INT_MAX || num < INT_MIN)
		return (handle_overflow(sign));
	return (num * sign);
}
