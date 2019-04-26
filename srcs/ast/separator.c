/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 04:53:28 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 10:22:31 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_ast	*ft_semicolon(t_lexer *lexer, t_ast *dad,
				t_lexer *new_separator)
{
	t_ast *new;

	new = new_node(new_separator, dad);
	if (new_separator->prev)
	{
		if (!(new->left = process(lexer, new, 1)))
			return (new);
		if (new->left)
			new->ret = new->left->ret;
	}
	if (new_separator->next)
	{
		new->right = process(lexer, new, 2);
		if (new->right)
			new->ret = new->right->ret;
	}
	return (new);
}

static t_ast	*ft_and(t_lexer *lexer, t_ast *dad, t_lexer *new_separator)
{
	t_ast *new;

	if (!(new = new_node(new_separator, dad)))
		ft_fatalexit("New_node inseparator.c");
	new->ret = 1;
	if (!new_separator->prev || !new_separator->next)
	{
		ft_puterror("syntax error near unexpected token '&&'");
		new->ret = -1;
		return (new);
	}
	if (new_separator->prev)
		new->left = process(lexer, new, 1);
	if (new_separator->next && new->left && new->left->ret == 0)
	{
		if ((new->right = process(lexer, new, 2)) && new->right->ret == 0)
			new->ret = 0;
	}
	return (new);
}

static t_ast	*ft_or(t_lexer *lexer, t_ast *dad, t_lexer *new_separator)
{
	t_ast *new;

	new = new_node(new_separator, dad);
	if (!new_separator->prev || !new_separator->next)
	{
		ft_puterror("syntax error near unexpected token '||'");
		new->ret = -1;
		return (new);
	}
	if (new_separator->prev)
	{
		new->left = process(lexer, new, 1);
		if ((new->ret = new->left->ret) == 0)
			return (new);
	}
	if (new_separator->next)
	{
		new->right = process(lexer, new, 2);
		new->ret = new->right->ret;
	}
	return (new);
}

t_ast			*operators(t_lexer *lexer, t_lexer *new_separator, t_ast *dad)
{
	t_ast *new;

	new_separator->status = 1;
	new = NULL;
	if (new_separator->type == SEMICOLON)
		new = ft_semicolon(lexer, dad, new_separator);
	if (new_separator->type == T_AND)
		new = ft_and(lexer, dad, new_separator);
	if (new_separator->type == T_OR)
		new = ft_or(lexer, dad, new_separator);
	if (new_separator->type == PIPE)
		new = ft_pipe(lexer, dad, new_separator);
	if (new->ret == -1)
		free_ast(&new);
	return (new);
}
