/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:20:06 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:08:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	handle_format_specifier_fd(int fd, va_list args, char c, int *counter)
{
	if (c == 'd' || c == 'i')
		putnbr_fd(fd, va_arg(args, int), counter);
	else if (c == 'u')
		putunbr_fd(fd, va_arg(args, unsigned int), counter);
	else if (c == 'c')
		putchar_fd(fd, va_arg(args, int), counter);
	else if (c == 's')
		putstr_fd(fd, va_arg(args, char *), counter);
	else if (c == 'x' || c == 'X')
		puthex_fd(fd, va_arg(args, unsigned int), c, counter);
	else if (c == 'p')
		putptr_fd(fd, va_arg(args, void *), counter);
	else if (c == '%')
		putchar_fd(fd, '%', counter);
	else 
	{
		putchar_fd(fd, '%', counter);
		putchar_fd(fd, c, counter);
	}
}

int	ft_printf_fd(int fd, const char *format, ...)
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
			handle_format_specifier_fd(fd, args, *format, &counter);
		}
		else
			putchar_fd(fd, *format, &counter);
		format++;
	}
	va_end(args);
	return (counter);
}
