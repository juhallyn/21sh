/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 03:50:12 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/02/15 21:28:55 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoins(int nb, ...)
{
	va_list ap;
	char	*s;
	char	*tmp;

	if (nb < 1)
		return (NULL);
	if (!(s = ft_strnew(1)))
		return (NULL);
	va_start(ap, nb);
	while (nb--)
	{
		tmp = s;
		s = ft_strjoin(s, va_arg(ap, char *));
		free(tmp);
	}
	return (s);
}
