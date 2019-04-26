/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_shortcuts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:33:35 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/03/15 18:08:28 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static inline void	move_next(int i, int j, t_line_stat *stat)
{
	while (j < i)
	{
		move_right(stat);
		j++;
	}
}

static inline void	move_prev(int i, int j, t_line_stat *stat)
{
	while (j < i)
	{
		move_left(stat);
		j++;
	}
}

static t_line		*init_tmp(t_line **edit_line, t_line_stat *stat, size_t *i,\
					bool next)
{
	t_line	*tmp;

	tmp = move_list_to_cursor(edit_line, stat->cursor_index);
	if (next)
	{
		if (tmp->next)
			tmp = tmp->next;
		while (tmp->c == ' ' && tmp->next)
		{
			tmp = tmp->next;
			*i = *i + 1;
		}
	}
	else
	{
		if (!tmp && !tmp->c)
			return (NULL);
		while (tmp->c == ' ' && tmp->prev->c)
		{
			tmp = tmp->prev;
			*i = *i + 1;
		}
	}
	return (tmp);
}

void				go_to_next_word(t_line **edit_line, t_line_stat *stat)
{
	t_line	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tmp = init_tmp(edit_line, stat, &i, true);
	if (!i)
	{
		while (tmp->c != ' ' && tmp->next)
		{
			tmp = tmp->next;
			i++;
		}
	}
	if (!tmp->next)
		move_end(*edit_line, stat);
	else
		move_next(i, j, stat);
}

void				go_to_back_word(t_line **edit_line, t_line_stat *stat)
{
	t_line	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tmp = init_tmp(edit_line, stat, &i, false);
	if (!tmp)
		return ;
	if (!i)
	{
		while (tmp && tmp->c != ' ' && tmp->prev && tmp->prev->c)
		{
			tmp = tmp->prev;
			i++;
		}
	}
	if (!tmp || !tmp->c || !tmp->prev->c)
		move_begin(*edit_line, stat);
	else
		move_prev(i, j, stat);
}
