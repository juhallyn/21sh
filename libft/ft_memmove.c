/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 01:45:38 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/03/04 01:45:40 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*src2;
	char	*dest2;
	size_t	i;

	i = -1;
	src2 = (char *)src;
	dest2 = (char *)dest;
	if (src2 > dest2)
		while (++i < n)
			*(dest2 + i) = *(src2 + i);
	else
		while (n--)
			*(dest2 + n) = *(src2 + n);
	return ((void *)dest2);
}
