/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 23:28:34 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/02/07 01:49:59 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*str;
	int		i;

	i = 0;
	if (n < 1 || !s || !(str = malloc(n + 1)))
		return (NULL);
	while (s[i] && n--)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
