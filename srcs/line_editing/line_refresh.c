/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_refresh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 08:12:11 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/18 16:07:14 by hp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static inline	void	move_up_del(void)
{
	size_t	i;

	i = 1;
	ft_put_termcap(MOVE_UP);
	while (i < std_singleton(NULL)->win.ws_col)
	{
		ft_put_termcap(MOVE_RIGHT);
		i++;
	}
	ft_put_termcap(DELETE_BEHIND);
}

void					refresh_line(t_line_stat *stat)
{
	t_std	*std;
	size_t	i;

	std = std_singleton(NULL);
	i = stat->cursor_index;
	move_begin(std->line, stat);
	ft_put_termcap(CLEAR);
	init_prompt_size(stat);
	print_prompt(0, stat->prompt_mode, stat->prompt_size);
	ft_put_termcap(SAVE_POS);
	if ((ioctl(0, TIOCGWINSZ, &(std)->win) == -1))
		ft_fatalexit("ioctl fail");
	if (std->line)
	{
		print_editing_list(std->line);
		move_begin(std->line, stat);
	}
	ft_put_termcap(REST_POS);
	while (stat->cursor_index < i)
		move_right(stat);
}

void					refresh_del(t_line *tmp, bool up, t_line_stat *stat)
{
	int		nb_char;
	size_t	j;

	nb_char = 0;
	j = stat->focus_line;
	if (!up)
		ft_put_termcap(MOVE_LEFT);
	else
		move_up_del();
	ft_put_termcap(SAVE_POS);
	ft_put_termcap(DELETE_BEHIND);
	if (tmp && tmp->next)
		print_editing_list(tmp->next);
	ft_put_termcap(REST_POS);
	ft_put_termcap(VISUAL_CURSOR);
}

void					refresh_add(t_line *tmp)
{
	ft_put_termcap(DELETE_BEHIND);
	ft_put_termcap(SAVE_POS);
	if (tmp && tmp->next)
		print_editing_list(tmp->next);
	ft_put_termcap(REST_POS);
	ft_put_termcap(MOVE_RIGHT);
}
