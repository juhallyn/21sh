/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parseur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 18:58:00 by hp                #+#    #+#             */
/*   Updated: 2018/06/19 20:08:00 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		check_type(t_lexer *node)
{
	if (node->type == AMPERSAND && (node->prev->type == REDIR_INF
	|| node->prev->type == REDIR_SUP))
		;
	else if (node->prev->type < 13 || node->prev->type == D_REDIR_INF \
	|| node->prev->type == D_REDIR_SUP || node->prev->type > STD_SEPARATOR)
		return (parse_error_near(node->prev->data));
	if (node->next->type == AMPERSAND && node->next->next
	&& node->next->next->type == WORD && is_nb(node->next->next->data) == 0)
		;
	else if ((node->next->type < DOLLAR && node->next->type != D_REDIR_INF \
	&& node->next->type != D_REDIR_SUP) || node->next->type > STD_SEPARATOR)
		return (parse_error_near(node->next->data));
	return (0);
}

static int		check_node(t_lexer *node)
{
	t_lexer	*out_space;

	out_space = NULL;
	if ((!node->prev &&
	!(node->type == D_REDIR_SUP || node->type == REDIR_SUP)) || !node->next)
		return (parse_error_near(node->data));
	if (check_type(node) == -1)
		return (-1);
	if (node->prev->type == STD_SEPARATOR)
		out_space = node->prev->prev;
	if (out_space)
		if ((out_space->type < DOLLAR && out_space->type \
		!= D_REDIR_INF && out_space->type != D_REDIR_SUP) \
		|| out_space->type > STD_SEPARATOR)
			return (parse_error_near(out_space->data));
	if (node->next->type == STD_SEPARATOR)
		out_space = node->next->next;
	if (out_space)
	{
		if ((out_space->type < DOLLAR && out_space->type \
		!= D_REDIR_INF && out_space->type != D_REDIR_SUP) \
		|| out_space->type > STD_SEPARATOR)
			return (parse_error_near(out_space->data));
	}
	return (0);
}

static int		check_redir_syntax(t_lexer *node)
{
	t_lexer		*out_space;

	out_space = node->next;
	if (node->type == D_REDIR_SUP || node->type == REDIR_SUP \
	|| node->type == REDIR_INF || node->type == D_REDIR_INF)
	{
		if (!node->next)
			return (parse_error_near("\\n"));
		if (node->next && node->next->type == STD_SEPARATOR)
			out_space = node->next->next;
		if (out_space)
		{
			if (out_space->type != WORD && out_space->type != AMPERSAND)
				return (parse_error_near(out_space->data));
		}
	}
	return (0);
}

int				syntax_parseur(t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->type == T_AND || lexer->type == T_OR \
		|| lexer->type == PIPE || lexer->type == AMPERSAND)
		{
			if (check_node(lexer) == -1)
			{
				free_lexer(&lexer);
				return (-1);
			}
		}
		if (lexer->type <= 9 && lexer->type >= 6)
		{
			if ((check_redir_syntax(lexer)) == -1)
			{
				free_lexer(&lexer);
				return (-1);
			}
		}
		lexer = lexer->next;
	}
	return (0);
}
