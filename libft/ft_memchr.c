/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 02:55:44 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/03/04 02:55:48 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	char	ch;

	ch = (char)c;
	str = (char *)s;
	while (n--)
	{
		if (*str == ch)
			return (str);
		str++;
	}
	return (0);
}
