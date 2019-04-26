/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 18:58:00 by hp                #+#    #+#             */
/*   Updated: 2018/06/19 20:08:00 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		lexer_add_end(t_lexer **lexer, char *data, t_token type)
{
	t_lexer		*tmp;

	if (!*lexer)
	{
		*lexer = create_lexer_node(data, type);
		return ;
	}
	tmp = *lexer;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = create_lexer_node(data, type);
	tmp->next->prev = tmp;
	tmp->next->next = NULL;
}

t_lexer		*create_lexer_node(char *data, t_token type)
{
	t_lexer		*node;

	node = NULL;
	node = (t_lexer*)malloc(sizeof(*node));
	if (!node)
		ft_fatalexit("allocation fail for `node` in create_lexer_node");
	if (data)
		node->data = ft_strdup(data);
	else
		node->data = NULL;
	node->type = type;
	node->status_line = OFF;
	node->status = 0;
	node->path_heredoc = NULL;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}
