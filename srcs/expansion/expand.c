/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 06:16:00 by hp                #+#    #+#             */
/*   Updated: 2018/06/18 20:12:32 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*expand_var(char *str, int len, int i)
{
	char	*var;
	int		j;
	t_env	*env;

	j = 0;
	var = NULL;
	var = ft_strnew(len);
	if (!var)
		ft_fatalexit("allocation error");
	while (--len >= 0)
		var[len] = str[--i];
	env = env_search(var);
	if (!env || !env->value)
		ft_strdel(&var);
	if (env)
	{
		ft_strdel(&var);
		var = ft_strdup(env->value);
	}
	return (var);
}

void		expand_modif(char **str, char *var, int len, int i)
{
	char	*new_str;
	char	*orig;
	char	*begin;
	char	*end;
	int		nb_offset;

	i_exp(&new_str, &orig, &begin, &end);
	nb_offset = (i - (len + 1));
	orig = *str;
	begin = ft_strsub(orig, 0, nb_offset);
	if (var == NULL)
	{
		end = ft_strsub(orig, (nb_offset + len + 1), (ft_strlen(orig)));
		new_str = ft_strjoins(2, begin, end);
	}
	if (var != NULL)
	{
		end = ft_strsub(orig, (nb_offset + len + 1), (ft_strlen(orig)));
		new_str = ft_strjoins(3, begin, var, end);
		ft_strdel(&var);
	}
	ft_strdel(&begin);
	ft_strdel(&end);
	ft_strdel(&orig);
	*str = new_str;
}

static void	expand_scan(t_lexer *lexer, char *var, int len, int i)
{
	while (lexer->data[i])
	{
		if ((lexer->data[i] == '$')
		&& !is_escape(lexer->data, i) && lexer->status_line != IN_QUOTE)
		{
			i++;
			while (lexer->data[i] && ft_ischar(lexer->data[i]) == 1 \
			&& lexer->data[i] != ' ' && (lexer->data[i] < 33 \
			|| lexer->data[i] > 64) && lexer->data[i] != '\n')
			{
				i++;
				len++;
			}
		}
		if (len > 0)
		{
			var = expand_var(lexer->data, len, i);
			expand_modif(&lexer->data, var, len, i);
			if (!var)
				i = 0;
			len = 0;
		}
		i++;
	}
}

void		tilde_expansion(t_lexer *tmp)
{
	char	*new;
	char	*home_path;

	new = NULL;
	home_path = NULL;
	if (env_search("HOME"))
		home_path = env_search("HOME")->value;
	if (home_path && tmp->data[1] && tmp->data[1] == '/')
	{
		if (!(new = ft_strjoin(home_path, &tmp->data[1])))
			ft_fatalexit("ft_strjoin tilde_expansion");
		ft_strdel(&tmp->data);
		tmp->data = new;
	}
	else if (home_path && !tmp->data[1])
	{
		if (!(new = ft_strjoin(home_path, &tmp->data[1])))
			ft_fatalexit("ft_strjoin tilde_expansion");
		ft_strdel(&tmp->data);
		tmp->data = new;
	}
}

void		expand(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->data && tmp->data[0] == '~'
		&& tmp->status_line == OFF)
			tilde_expansion(tmp);
		if (tmp->type == WORD)
			expand_scan(tmp, NULL, 0, 0);
		tmp = tmp->next;
	}
}
