/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:43:39 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 12:58:06 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_ast	*words(t_lexer *word, t_ast *parent)
{
	t_ast	*new;

	new = NULL;
	while (word->prev && word->prev->status != 1)
		word = word->prev;
	if (word->type == STD_SEPARATOR && word->next && word->next->status != 1)
		word = word->next;
	new = new_node(word, parent);
	new->type = WORD;
	if ((new_redirection(new->lexer_node)) == -1)
	{
		new->ret = -1;
		return (new);
	}
	new->argv = cmd_create(word);
	new->ret = new->argv[0] ? exec(new) : 0;
	struct_redir_destroy();
	return (new);
}

t_ast			*process(t_lexer *lexer, t_ast *parent, int info)
{
	t_lexer *operator;

	operator = NULL;
	operator = priority(parent, info);
	if (is_operator(operator) == 0)
		return (operators(lexer, operator, parent));
	else if (operator)
		return (words(operator, parent));
	return (NULL);
}
