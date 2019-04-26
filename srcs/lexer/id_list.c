/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 10:31:49 by hp                #+#    #+#             */
/*   Updated: 2018/06/17 04:52:19 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lexer_id		*create_lexer_id_node(char data, t_token type)
{
	t_lexer_id		*node;

	node = NULL;
	node = (t_lexer_id*)malloc(sizeof(*node));
	if (!node)
		ft_fatalexit("allocation fail for `node` in create_lexer_id_node");
	node->data = data;
	node->type = type;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void			lexer_id_add_end(t_lexer_id **lexer, char data, t_token type)
{
	t_lexer_id		*tmp;

	tmp = NULL;
	if (!*lexer)
	{
		*lexer = create_lexer_id_node(data, type);
		return ;
	}
	tmp = *lexer;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = create_lexer_id_node(data, type);
	tmp->next->prev = tmp;
}

t_lexer_id		*lexer_id_init(void)
{
	t_lexer_id	*node;

	node = NULL;
	node = (t_lexer_id*)malloc(sizeof(*node));
	if (!node)
		ft_fatalexit("allocation fail node in lexer_init");
	node->data = '\0';
	node->type = INIT;
	return (node);
}

void			free_lexer_id(t_lexer_id **lexer_id)
{
	t_lexer_id	*tmp;

	tmp = NULL;
	while (lexer_id && *lexer_id)
	{
		tmp = (*lexer_id)->next;
		free(*lexer_id);
		(*lexer_id) = tmp;
	}
	(*lexer_id) = NULL;
}
