/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 10:31:49 by hp                #+#    #+#             */
/*   Updated: 2018/06/17 04:52:19 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			ref_token2(t_lexer_id **lexer, char *str, int i)
{
	if (str[i] == CHAR_DQUOTE && !is_escape(str, i))
		lexer_id_add_end(lexer, str[i], DQUOTE);
	else if (str[i] == TOKEN_NEWLINE && !is_escape(str, i))
		lexer_id_add_end(lexer, str[i], NEWLINE);
	else if (str[i] == TOKEN_DOLLAR && !is_escape(str, i))
		lexer_id_add_end(lexer, str[i], DOLLAR);
	else
		lexer_id_add_end(lexer, str[i], WORD);
	return (i);
}

void				ref_token(t_lexer_id **lexer, char *str)
{
	size_t		i;
	size_t		start;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == TOKEN_SEMICOLON && !is_escape(str, i))
			lexer_id_add_end(lexer, str[i], SEMICOLON);
		else if (str[i] == TOKEN_REDIR_SUP && !is_escape(str, i))
			lexer_id_add_end(lexer, str[i], REDIR_SUP);
		else if (str[i] == TOKEN_REDIR_INF && !is_escape(str, i))
			lexer_id_add_end(lexer, str[i], REDIR_INF);
		else if (str[i] == TOKEN_REDIR_SUP && !is_escape(str, i))
			lexer_id_add_end(lexer, str[i], REDIR_SUP);
		else if (str[i] == TOKEN_PIPE && !is_escape(str, i))
			lexer_id_add_end(lexer, str[i], PIPE);
		else if (str[i] == TOKEN_AMPERSAND && !is_escape(str, i))
			lexer_id_add_end(lexer, str[i], AMPERSAND);
		else if (str[i] == CHAR_QUOTE && !is_escape(str, i))
			lexer_id_add_end(lexer, str[i], QUOTE);
		else
			i = ref_token2(lexer, str, i);
		i++;
	}
}

t_lexer_id			*analyse(char *command)
{
	t_lexer_id	*lexer;
	char		**split;
	size_t		i;
	size_t		token_index;

	i = 0;
	lexer = NULL;
	token_index = 0;
	if (!command)
		return (NULL);
	split = lexer_split(command);
	while (split[i])
	{
		ref_token(&lexer, split[i]);
		i++;
		if (split[i])
			lexer_id_add_end(&lexer, ' ', STD_SEPARATOR);
	}
	array_free(&split);
	if (command)
		ft_strdel(&command);
	return (lexer);
}
