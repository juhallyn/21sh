/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 03:50:12 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/02/15 21:28:55 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;

	i = -1;
	if (!ft_strcmp((char *)needle, ""))
		return ((char *)haystack);
	if (haystack[0])
		while (haystack[++i])
			if (haystack[i] == needle[0])
				if (ft_strnequ((haystack + i), needle, ft_strlen(needle)))
					return ((char *)haystack + i);
	return (NULL);
}
