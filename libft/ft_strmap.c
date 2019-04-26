/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 19:57:26 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/03/03 19:57:29 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*str;

	i = -1;
	if (!s || !(str = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[++i])
		str[i] = f(s[i]);
	str[i] = '\0';
	return (str);
}
