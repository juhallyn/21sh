/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:46:23 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 03:32:36 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lexer			*move_to_end(t_lexer *separator, int info)
{
	t_lexer *lexer_tmp;
	t_std	*std;

	std = std_singleton(NULL);
	if ((info == 1 || info == 3) && separator)
		return (separator->prev);
	if ((info == 2 || info == 4) && separator)
		lexer_tmp = separator->next;
	else
		lexer_tmp = std->lexer;
	while (lexer_tmp->next && !lexer_tmp->next->status)
		lexer_tmp = lexer_tmp->next;
	return (lexer_tmp);
}

static int		priority2(t_lexer *tmp, int n)
{
	if (tmp && tmp->type == NEWLINE && tmp->status_line == 0)
		tmp->type = SEMICOLON;
	if (n == 0 && (tmp->type == SEMICOLON) && !tmp->status_line)
		return (0);
	if (n == 1 && tmp->type == PIPE && !tmp->status_line)
		return (0);
	if (n == 2 && (tmp->type == T_AND || tmp->type == T_OR)
	&& !tmp->status_line)
		return (0);
	if (n == 3 && (tmp->type >= REDIR_SUP && tmp->type <= D_REDIR_SUP)
	&& !tmp->status_line)
		return (0);
	return (1);
}

t_lexer			*priority(t_ast *parent, int info)
{
	t_lexer *tmp;
	t_lexer *end;
	int		n;

	end = move_to_end((parent ? parent->lexer_node : NULL), info);
	n = -1;
	while (++n <= 3)
	{
		tmp = end;
		while (tmp && !tmp->status)
		{
			if (priority2(tmp, n) == 0)
				return (tmp);
			tmp = tmp->prev;
		}
	}
	return (end);
}
