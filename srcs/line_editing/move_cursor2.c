/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:56:14 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/03/15 18:11:34 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		move_begin(t_line *edit_line, t_line_stat *stat)
{
	t_line	*tmp;

	tmp = edit_line;
	if (!tmp)
		return ;
	tmp = move_list_to_cursor(&tmp, stat->cursor_index);
	if (!tmp->c)
		return ;
	while (tmp)
	{
		move_left(stat);
		tmp = tmp->prev;
	}
}

void		move_end(t_line *edit_line, t_line_stat *stat)
{
	t_line	*tmp;

	tmp = edit_line;
	tmp = move_list_to_cursor(&tmp, stat->cursor_index);
	if (!tmp)
		return ;
	if (!tmp->c && tmp->next && stat->prompt_size != 8)
		tmp = tmp->next;
	while (tmp && (stat->nb_char > stat->cursor_index))
	{
		move_right(stat);
		tmp = tmp->next;
	}
}
