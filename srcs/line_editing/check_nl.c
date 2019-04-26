/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 08:11:29 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 08:11:31 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	nl_backspace(t_line_stat *stat)
{
	t_std	*std;
	t_line	*tmp;

	tmp = NULL;
	std = std_singleton(NULL);
	tmp = move_list_to_cursor(&std->line, stat->cursor_index);
	if (tmp && tmp->c == '\n' && tmp->prev && tmp->prev->c == NEWLINE_ANSI)
		return (true);
	return (false);
}
