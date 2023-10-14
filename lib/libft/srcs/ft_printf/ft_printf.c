/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:20:06 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:07:03 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	handle_format_specifier(va_list args, char c, int *counter)
{
	if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(args, int), counter);
	else if (c == 'u')
		ft_putunbr(va_arg(args, unsigned int), counter);
	else if (c == 'c')
		ft_putchar(va_arg(args, int), counter);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), counter);
	else if (c == 'x' || c == 'X')
		ft_puthex(va_arg(args, unsigned int), c, counter);
	else if (c == 'p')
		ft_putptr(va_arg(args, void *), counter);
	else if (c == '%')
		ft_putchar('%', counter);
	else 
	{
		ft_putchar('%', counter);
		ft_putchar(c, counter);
	}
}

int	ft_printf(const char *format, ...)
{
	int				counter;
	va_list			args;

	counter = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			handle_format_specifier(args, *format, &counter);
		}
		else
			ft_putchar(*format, &counter);
		format++;
	}
	va_end(args);
	return (counter);
}
