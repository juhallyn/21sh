/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_adding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 21:09:44 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/03/20 12:13:10 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_middle(t_line *prev, char key, t_line *next)
{
	t_line	*new;

	new = init_line(key);
	prev->next = new;
	new->next = next;
	new->prev = prev;
	next->prev = new;
}

void	add_char(t_line **edit_line, int key, t_line_stat *stat)
{
	t_line	*tmp;

	tmp = move_list_to_cursor(edit_line, stat->cursor_index);
	if (!tmp || !tmp->next)
	{
		add_end(&tmp, key);
		if (key == NEWLINE_ANSI)
			ft_putchar_fd('^', 0);
		else if (key == '\n')
			ft_putchar_fd('J', 0);
		else
			ft_putchar_fd(key, 0);
	}
	else
	{
		if (tmp && tmp->next)
		{
			add_middle(tmp, key, tmp->next);
			refresh_add(tmp);
		}
	}
}

void	add_end(t_line **edit_line, int key)
{
	t_line	*tmp;

	tmp = NULL;
	if (!*edit_line)
	{
		*edit_line = init_line(key);
		return ;
	}
	tmp = *edit_line;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = init_line(key);
	tmp->next->prev = tmp;
	tmp->next->next = NULL;
}
