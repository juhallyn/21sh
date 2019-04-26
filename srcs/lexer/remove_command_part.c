/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_command_part.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:22:51 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 17:24:13 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*remove_newline_ansi(char *command)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	if (!command)
		return (NULL);
	new = (char *)ft_memalloc(sizeof(char*) * ft_strlen(command));
	if (!new)
		ft_fatalexit("allocation fail of new in (remove_newline_ansi)");
	while (command[i])
	{
		if ((ft_strncmp(command + i, "\032J", 2) == 0))
		{
			new[j] = '\n';
			i++;
		}
		else
			new[j] = command[i];
		i++;
		j++;
	}
	ft_strdel(&command);
	return (new);
}

static int		remove_useless_semicon2(t_lexer **lexer)
{
	t_lexer *tmp;

	if ((*lexer)->prev && (*lexer)->prev->type == STD_SEPARATOR)
	{
		tmp = (*lexer)->prev;
		if (tmp->prev)
			tmp->prev->next = *lexer;
		(*lexer)->prev = tmp->prev;
		ft_strdel(&tmp->data);
		free(tmp);
	}
	if ((*lexer)->prev &&
	((*lexer)->prev->type == SEMICOLON || (*lexer)->prev->type == 12)
	&& (*lexer)->status_line == OFF)
	{
		tmp = (*lexer)->prev;
		if ((*lexer)->next)
			(*lexer)->next->prev = tmp;
		tmp->next = (*lexer)->next;
		ft_strdel(&(*lexer)->data);
		free(*lexer);
		*lexer = tmp;
		return (1);
	}
	return (0);
}

t_lexer			*remove_useless_semicon(t_lexer *lexer)
{
	t_lexer *tmp;

	while ((tmp = lexer))
	{
		if (lexer->type == SEMICOLON || lexer->type == 12)
		{
			if (lexer->prev && (remove_useless_semicon2(&lexer) == 1))
				continue ;
			else if (!lexer->prev)
			{
				tmp = lexer;
				if ((lexer = lexer->next))
					lexer->prev = NULL;
				ft_strdel(&tmp->data);
				free(tmp);
			}
		}
		if (lexer && lexer->next)
			lexer = lexer->next;
		else
			break ;
	}
	while (lexer && lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}
