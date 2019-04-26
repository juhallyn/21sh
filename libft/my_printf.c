/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 03:50:12 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/02/15 21:28:55 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		my_printf(const char *str, int fd, ...)
{
	va_list ap;

	va_start(ap, fd);
	while (*str)
	{
		if (*str != '%')
			write(fd, str, 1);
		if (*str == '%')
		{
			if (*++str == 's')
				ft_putstr_fd(va_arg(ap, char *), fd);
			if (*str == 'c')
				ft_putchar_fd((char)va_arg(ap, int), fd);
			if (*str == 'd' || *str == 'i')
				ft_putnbr_fd(va_arg(ap, int), fd);
		}
		str++;
	}
}
