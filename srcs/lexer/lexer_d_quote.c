/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_d_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:20:40 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 20:53:18 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_lexer		*d_quote_status_line(t_lexer *lexer)
{
	t_lexer		*tmp;

	tmp = lexer;
	if (lexer->type == DQUOTE)
	{
		tmp = tmp->next;
		while (tmp && tmp->type != DQUOTE)
		{
			tmp->status_line = IN_DQUOTE;
			tmp->type = WORD;
			tmp = tmp->next;
		}
	}
	else if (lexer->type == QUOTE)
	{
		tmp = tmp->next;
		while (tmp && tmp->type != QUOTE)
		{
			tmp->status_line = IN_QUOTE;
			tmp->type = WORD;
			tmp = tmp->next;
		}
	}
	return (tmp);
}

static t_lexer		*init_d_quote_status(t_lexer *lexer)
{
	while (lexer && lexer->next)
	{
		if (lexer->status_line == OFF
		&& (lexer->type == DQUOTE || lexer->type == QUOTE))
			lexer = d_quote_status_line(lexer);
		if (lexer && lexer->next)
			lexer = lexer->next;
	}
	while (lexer && lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}

static t_lexer		*quote_del(t_lexer *lexer)
{
	t_lexer *tmp;

	while (lexer && lexer->next)
	{
		if (lexer->type == QUOTE
		|| ((lexer->type == DQUOTE) && lexer->status_line == OFF))
		{
			tmp = lexer;
			lexer = lexer->next;
			if (tmp->prev)
				tmp->prev->next = lexer;
			if (lexer)
				lexer->prev = tmp->prev;
			if (tmp->data)
				ft_strdel(&tmp->data);
			free(tmp);
		}
		else if (lexer->next)
			lexer = lexer->next;
	}
	while (lexer && lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}

static t_lexer		*word_join(t_lexer *lexer)
{
	char	*tmp_str;
	t_lexer	*tmp;

	while (lexer && lexer->next)
	{
		if (lexer->type == WORD && lexer->next->type == WORD)
		{
			tmp = lexer;
			lexer = lexer->next;
			tmp_str = ft_strjoin(tmp->data, lexer->data);
			tmp->data ? ft_strdel(&tmp->data) : NULL;
			if (lexer->data)
				ft_strdel(&lexer->data);
			lexer->data = tmp_str ? tmp_str : NULL;
			if (lexer)
				if ((lexer->prev = tmp->prev))
					tmp->prev->next = lexer;
			free(tmp);
		}
		else if (lexer->next)
			lexer = lexer->next;
	}
	while (lexer && lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}

t_lexer				*lexer_d_quote(t_lexer *lexer)
{
	if (lexer)
		lexer = init_d_quote_status(lexer);
	if (lexer)
		lexer = quote_del(lexer);
	if (lexer)
		lexer = word_join(lexer);
	return (lexer);
}
