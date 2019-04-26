/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:20:40 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 20:53:18 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			free_lexer(t_lexer **lexer)
{
	t_lexer		*tmp;

	tmp = NULL;
	while (lexer && *lexer && (*lexer)->prev)
		*lexer = (*lexer)->prev;
	while (*lexer)
	{
		tmp = (*lexer);
		(*lexer) = (*lexer)->next;
		if (tmp->data)
			ft_strdel(&tmp->data);
		if (tmp->path_heredoc)
			ft_strdel(&tmp->path_heredoc);
		free(tmp);
	}
	(*lexer) = NULL;
}

static	void	join_redir(t_lexer_id *id, size_t *len, \
				t_token *act_type)
{
	*len = *len + 1;
	if (*act_type == REDIR_SUP)
		id->type = D_REDIR_SUP;
	if (*act_type == AMPERSAND)
		id->type = T_AND;
	if (*act_type == PIPE)
		id->type = T_OR;
	if (*act_type == REDIR_INF)
		id->type = D_REDIR_INF;
}

void			join_lexical_operator(t_lexer_id *id, t_lexer **lexer, \
				size_t *len, t_token *act_type)
{
	if (*len == 1 && id->type == *act_type && (*act_type == REDIR_SUP
	|| *act_type == REDIR_INF || *act_type == AMPERSAND
	|| *act_type == AMPERSAND || *act_type == PIPE))
		join_redir(id, len, act_type);
	else
	{
		add_token(id->prev, lexer, *len);
		*act_type = id->type;
		*len = 1;
	}
}

void			tokenizer(t_lexer_id *lexer_id, t_lexer **lexer)
{
	t_lexer_id	*id_tmp;
	t_token		act_type;
	size_t		len;

	if (!lexer_id)
		return ;
	len = 0;
	id_tmp = NULL;
	act_type = lexer_id->type;
	while (lexer_id)
	{
		if ((lexer_id->type == WORD || lexer_id->type == DOLLAR) \
		&& (act_type == WORD || act_type == DOLLAR))
			len++;
		else
			join_lexical_operator(lexer_id, lexer, &len, &act_type);
		id_tmp = lexer_id;
		lexer_id = lexer_id->next;
	}
	if (len)
		add_token(id_tmp, lexer, len);
}

t_lexer			*lexing(char *command)
{
	t_lexer_id		*lexer_id;
	t_lexer			*lexer;

	lexer = NULL;
	if (!command)
		return (NULL);
	command = remove_newline_ansi(command);
	lexer_id = analyse(command);
	tokenizer(lexer_id, &lexer);
	free_lexer_id(&lexer_id);
	if (!(lexer = lexer_d_quote(lexer)))
		return (NULL);
	if (!(lexer = remove_useless_semicon(lexer)))
	{
		std_singleton(NULL)->ret = 0;
		return (NULL);
	}
	std_singleton(NULL)->ret = search_heredoc(lexer);
	if ((std_singleton(NULL)->ret = syntax_parseur(lexer)) == -1)
		return (NULL);
	expand(&lexer);
	return (lexer);
}
