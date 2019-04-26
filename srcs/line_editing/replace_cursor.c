/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 20:47:53 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/03/15 17:48:26 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		replace_cursor(t_line_stat *stat, t_line *edit_line)
{
	t_line	*tmp;
	size_t	i;

	i = 0;
	tmp = move_list_to_cursor(&edit_line, stat->cursor_index);
	while (tmp && tmp->next)
	{
		move_right(stat);
		tmp = tmp->next;
		i++;
	}
	while (i > 0)
	{
		move_left(stat);
		i--;
	}
}

void		check_insert_line(t_line **edit_line, t_line_stat *stat)
{
	t_std	*std;
	size_t	last_char;

	std = std_singleton(NULL);
	last_char = stat->nb_char + stat->prompt_size;
	if (last_char == (std->win.ws_col * (stat->nb_line)))
	{
		replace_cursor(stat, *edit_line);
		stat->nb_line++;
	}
}

void		check_del_line(t_line_stat *stat)
{
	t_std	*std;
	size_t	last_char;

	std = std_singleton(NULL);
	last_char = stat->nb_char + stat->prompt_size;
	if (last_char == (std->win.ws_col * (stat->nb_line - 1)))
		stat->nb_line--;
}
