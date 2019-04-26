/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hp <hp@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 06:05:00 by hp                #+#    #+#             */
/*   Updated: 2019/04/11 11:06:43 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	d_quote(const char *s, int n)
{
	bool	quote;
	bool	dquote;
	int		i;

	i = 0;
	quote = false;
	dquote = false;
	while (s[i + n] && ((s[i + n] != ' ' && s[i + n] != '\t') \
	|| quote == true || dquote == true))
	{
		if (!is_escape((char *)s, n + i))
		{
			dquote = (s[i + n] == '"') ? !dquote : dquote;
			quote = (s[i + n] == '\'') ? !quote : quote;
		}
		i++;
	}
	return (i);
}

static int	count_word(char const *s)
{
	int	i;
	int	word;

	if (s == NULL)
		return (0);
	word = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		i += d_quote(s, i);
		if (i > 0 && (s[i - 1] != ' ' && s[i - 1] != '\t'))
			word++;
	}
	return (word);
}

char		**lexer_split(char *s)
{
	char	**res;
	int		i;
	int		j;
	int		word;

	word = count_word(s);
	if (!s || !(res = ft_memalloc(sizeof(char **) * (word + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		word = d_quote(s, i);
		if (word > 0)
			res[j++] = ft_strsub(s, i, word);
		i += word;
	}
	res[j] = NULL;
	return (res);
}
