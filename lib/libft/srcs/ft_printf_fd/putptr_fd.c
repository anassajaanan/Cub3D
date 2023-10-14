/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putptr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:24:41 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/14 09:08:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	putptr_fd(int fd, void *ptr, int *counter)
{
	if (ptr == NULL)
		putstr_fd(fd, "0x0", counter);
	else
	{
		putstr_fd(fd, "0x", counter);
		puthex_fd(fd, (uintptr_t)ptr, 'x', counter);
	}
}
