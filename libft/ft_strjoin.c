/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 02:26:13 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/01/31 01:06:58 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		begin;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	s = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s)
		return (NULL);
	ft_strcpy(s, s1);
	begin = ft_strlen(s1);
	while (s2[i])
	{
		s[begin] = s2[i];
		i++;
		begin++;
	}
	s[begin] = '\0';
	return (s);
}
