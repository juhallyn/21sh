/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 14:29:04 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/04/06 15:23:37 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_line		*delete(t_line **edit_line, size_t cursor_index)
{
	size_t	i;
	t_line	*tmp;

	i = 0;
	tmp = *edit_line;
	while (i < cursor_index && tmp && tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	delete_char(&tmp);
	return (tmp);
}

void		insertion(t_line_stat *stat, t_line **edit_line, int key)
{
	t_std	*std;
	t_line	*tmp;

	std = std_singleton(NULL);
	add_char(edit_line, key, stat);
	increment_stat(&stat);
	check_insert_line(edit_line, stat);
	tmp = move_list_to_cursor(edit_line, stat->cursor_index);
	if (stat->win_index == (std->win.ws_col * (stat->focus_line)))
	{
		ft_put_termcap(MOVE_DOWN);
		stat->focus_line++;
	}
}

void		backspace_delete(t_line_stat *stat, t_line **edit_line)
{
	t_line	*tmp;
	t_std	*std;
	bool	up;
	bool	is_nl;

	up = false;
	tmp = NULL;
	std = std_singleton(NULL);
	is_nl = false;
	if (stat->cursor_index)
	{
		is_nl = nl_backspace(stat);
		tmp = delete(edit_line, stat->cursor_index);
		decrement_stat(&stat);
		check_del_line(stat);
		if ((stat->win_index + 1) == (std->win.ws_col * (stat->focus_line - 1)))
		{
			up = true;
			stat->focus_line--;
		}
		refresh_del(tmp, up, stat);
	}
	if (is_nl)
		backspace_delete(stat, edit_line);
}

void		del_delete(t_line_stat *stat, t_line **edit_line)
{
	t_line	*tmp;

	tmp = move_list_to_cursor(edit_line, stat->cursor_index);
	if (tmp->next)
	{
		move_right(stat);
		backspace_delete(stat, edit_line);
	}
}

void		delete_line(t_line **edit_line, t_line_stat *stat)
{
	size_t	i;

	i = stat->nb_char;
	move_end(*edit_line, stat);
	while (i > 0)
	{
		backspace_delete(stat, edit_line);
		i--;
	}
}
