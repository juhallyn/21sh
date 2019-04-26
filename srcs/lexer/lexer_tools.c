/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 02:37:30 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 20:04:45 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool			is_escape(char *str, size_t i)
{
	size_t	j;
	bool	status;

	status = false;
	if (i == 0)
		i = 1;
	if (str && str[i])
	{
		j = i - 1;
		while (str[j])
		{
			if (str[j] == '\\')
				status = !status;
			else
				return (status);
			j--;
		}
	}
	return (status);
}

static void		check_io_number(t_lexer *lexer)
{
	size_t		i;

	i = 0;
	if (!lexer)
		return ;
	while (lexer->next)
		lexer = lexer->next;
	if (lexer && lexer->data && ft_isdigit(lexer->data[0]) == 1
	&& ft_strlen(lexer->data) == 1)
		lexer->type = IO_NUMBER;
}

void			add_token(t_lexer_id *id_ptr, t_lexer **lexer, size_t len)
{
	size_t	i;
	char	*data;
	t_token	type;

	if (!id_ptr)
		return ;
	i = 0;
	type = id_ptr->type;
	if (type == DOLLAR)
		type = WORD;
	if (!(data = ft_strnew(len)))
		ft_fatalexit("allocation failed to `data` in add_token()");
	if (type == REDIR_SUP || type == D_REDIR_SUP
	|| type == REDIR_INF || type == D_REDIR_INF)
		check_io_number(*lexer);
	while (len != 0 && id_ptr)
	{
		data[len - 1] = id_ptr->data;
		id_ptr = id_ptr->prev;
		len--;
		if (!len)
			lexer_add_end(lexer, data, type);
	}
	if (data)
		ft_strdel(&data);
}

void			print_lexer_list(t_lexer *lexer)
{
	if (!lexer)
		return ;
	while (lexer)
	{
		if (lexer->data)
			ft_putendl(lexer->data);
		lexer = lexer->next;
	}
}
