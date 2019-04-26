/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcolor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 19:48:11 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/12/25 19:48:12 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putcolor(int nb, ...)
{
	va_list	ap;
	char	color;

	ft_putstr("\x1B[0m");
	if (nb > 0)
		va_start(ap, nb);
	while (nb-- > 0 && (color = va_arg(ap, int)))
	{
		color == 'r' ? ft_putstr("\x1B[31m") : 0;
		color == 'v' ? ft_putstr("\x1B[32m") : 0;
		color == 'y' ? ft_putstr("\x1B[33m") : 0;
		color == 'b' ? ft_putstr("\x1B[34m") : 0;
		color == 'p' ? ft_putstr("\x1B[35m") : 0;
		color == 'c' ? ft_putstr("\x1B[36m") : 0;
		color == 'g' ? ft_putstr("\x1B[37m") : 0;
		color == 'G' ? ft_putstr("\x1B[1m") : 0;
		color == 'B' ? ft_putstr("\x1B[3m") : 0;
		color == 'U' ? ft_putstr("\x1B[4m") : 0;
	}
}
