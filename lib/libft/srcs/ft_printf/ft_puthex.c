/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:24:12 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:08:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_puthex(uintptr_t n, char case_type, int *counter)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (case_type == 'X')
		hex = "0123456789ABCDEF";
	if (n >= 16)
	{
		ft_puthex(n / 16, case_type, counter);
		ft_puthex(n % 16, case_type, counter);
	}
	else
		ft_putchar(hex[n], counter);
}
