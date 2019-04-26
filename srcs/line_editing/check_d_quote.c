/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_d_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 08:11:22 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 20:50:06 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			tmp_is_escape(t_line *tmp)
{
	bool	status;

	status = false;
	if (!tmp->prev)
		return (false);
	tmp = tmp->prev;
	while (tmp && tmp->c == '\\')
	{
		status = !status;
		tmp = tmp->prev;
	}
	return (status);
}

int					check_close_d_quote(t_line *edit_line)
{
	int		start;

	start = to_close(edit_line);
	return (start);
}

static inline void	check_close_routine(char c, int *start, bool *quote, \
					bool *dquote)
{
	if ((c == CHAR_QUOTE && (!*start))
	|| ((*start) == CHAR_QUOTE && c == CHAR_QUOTE))
	{
		if (!*start)
			*start = CHAR_QUOTE;
		*quote = (!*quote);
		if (*quote == true && *start == CHAR_QUOTE)
			*start = 0;
	}
	if (start && ((c == CHAR_DQUOTE && (!*start))
	|| (*start && *start == CHAR_DQUOTE && c == CHAR_DQUOTE)))
	{
		if (!*start)
			*start = CHAR_DQUOTE;
		*dquote = (!*dquote);
		if (*dquote == true && *start == CHAR_DQUOTE)
			*start = 0;
	}
}

int					to_close(t_line *edit_line)
{
	bool	quote;
	bool	dquote;
	int		start;

	start = 0;
	quote = true;
	dquote = true;
	while (edit_line)
	{
		if (edit_line->c == CHAR_QUOTE || edit_line->c == CHAR_DQUOTE)
		{
			if (tmp_is_escape(edit_line) == false)
				check_close_routine(edit_line->c, &start, &quote, &dquote);
		}
		edit_line = edit_line->next;
	}
	return (start);
}
