/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 14:43:31 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/03/10 14:43:34 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	i;
	int	word;

	if (s == NULL)
		return (0);
	word = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		if (i > 0 && s[i - 1] != c)
			word++;
	}
	return (word);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;
	int		word;

	word = count_word(s, c);
	i = 0;
	j = 0;
	res = ft_memalloc(sizeof(char **) * (word + 1));
	if (!res || !s)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		word = 0;
		while (s[i + word] && s[i + word] != c)
			word++;
		if (word > 0)
			res[j] = ft_strsub(s, i, word);
		j++;
		i = i + word;
	}
	res[j] = NULL;
	return (res);
}
