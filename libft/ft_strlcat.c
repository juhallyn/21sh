/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 00:09:44 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/03/13 00:09:53 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(char *dest, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (dest[i] == 0)
			return (i);
		i++;
	}
	return (size);
}

size_t			ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	n;
	size_t	i;
	size_t	ret;

	i = 0;
	if (size <= (ft_strnlen(dest, size) + 1))
		return (ft_strnlen(dest, size) + ft_strlen(src));
	n = ft_strlen(dest);
	ret = n + ft_strlen(src);
	while (src[i])
	{
		if (n < size - 1)
		{
			dest[n] = src[i];
			n++;
		}
		i++;
	}
	dest[n] = 0;
	return (ret);
}
