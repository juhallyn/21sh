/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:50:19 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 20:12:47 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static inline int	switch_key_extended(t_line **edit_line, t_line_stat *stat,\
					int key)
{
	if (key == ALT_LEFT)
	{
		go_to_back_word(edit_line, stat);
		go_to_back_word(edit_line, stat);
	}
	else if (key == ALT_RIGHT)
	{
		go_to_next_word(edit_line, stat);
		go_to_next_word(edit_line, stat);
	}
	return (0);
}

static inline int	switch_key(t_line **edit_line, t_line_stat *stat, int key)
{
	if (ft_ischar(key) != 0)
		insertion(stat, edit_line, key);
	else if (key == DEL)
		del_delete(stat, edit_line);
	else if (key == SIZE_CHANGED || key == CTRL_L)
		refresh_line(stat);
	else if (key == LEFT_ARROW)
		move_left(stat);
	else if (key == RIGHT_ARROW && (stat->nb_char > stat->cursor_index))
		move_right(stat);
	else if (key == UP_ARROW && !std_singleton(NULL)->eof_str)
		read_history_up(edit_line, stat);
	else if (key == DOWN_ARROW && !std_singleton(NULL)->eof_str)
		read_history_down(edit_line, stat);
	else if (key == BACKSPACE)
		backspace_delete(stat, edit_line);
	else if (key == HOME)
		move_begin(*edit_line, stat);
	else if (key == END)
		move_end(*edit_line, stat);
	else
		switch_key_extended(edit_line, stat, key);
	return (0);
}

int					ft_copy_paste(t_line **edit_line,
					t_line_stat *stat, int key)
{
	t_std	*std;

	std = std_singleton(NULL);
	if (std->clipboard && key == CTRL_H)
	{
		paste_mod(std->clipboard, edit_line, stat);
		return (0);
	}
	if (std->clipboard)
		ft_strdel(&std->clipboard);
	if (key == CTRL_G)
		std->clipboard = list_to_str(edit_line, false);
	if (key == CTRL_F)
	{
		std->clipboard = list_to_str(edit_line, false);
		delete_line(edit_line, stat);
	}
	return (0);
}

int					ft_edit_line(t_line **edit_line,
					t_line_stat *stat, int key)
{
	t_std		*std;
	int			ret_quote;

	ret_quote = 0;
	std = std_singleton(NULL);
	stat->win_index = stat->prompt_size + stat->cursor_index;
	if (key == ENTER || (key == CTRL_D && std->eof_str))
		return (newline_eof(edit_line, stat, key));
	if (key == PROMPT_ERR && std->eof_str)
		return (newline_eof(edit_line, stat, key));
	if (key == PROMPT_ERR)
		return (error_key(edit_line, stat, key));
	if (key == CTRL_F || key == CTRL_G || key == CTRL_H)
		return (ft_copy_paste(edit_line, stat, key));
	if (key == CTRL_D)
		return ((eof_key(edit_line, stat) == 1) ? -1 : 0);
	else if (key == SIZE_CHANGED || key == CTRL_L)
		refresh_line(stat);
	else
		return (switch_key(edit_line, stat, key));
	return (0);
}
