/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 08:10:21 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 08:10:29 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		insert_history(t_line_stat *stat, t_line **edit_line, char *data)
{
	size_t	i;

	i = 0;
	if (!data)
		return ;
	while (data[i])
	{
		if ((ft_strncmp(data + i, "\032J", 2) == 0))
		{
			insertion(stat, edit_line, NEWLINE_ANSI);
			insertion(stat, edit_line, '\n');
			i++;
		}
		else
			insertion(stat, edit_line, data[i]);
		i++;
	}
}

static char	*save_current_command(t_line *edit_line)
{
	char	*command;
	size_t	i;

	i = 0;
	command = NULL;
	if (edit_line->next)
		edit_line = edit_line->next;
	else
		return (NULL);
	command = malloc_str(edit_line);
	while (edit_line)
	{
		command[i] = edit_line->c;
		edit_line = edit_line->next;
		i++;
	}
	command[i] = '\0';
	return (command);
}

void		read_history_up(t_line **edit_line, t_line_stat *stat)
{
	t_std			*std;
	t_hist_data		*history_tab;

	std = std_singleton(NULL);
	history_tab = std->history->history_tab;
	if (std->history->nb_hist_line >= HIST_SIZE)
		return ;
	if (stat->history_index == std->history->nb_hist_line)
	{
		if (std->history->current_line)
			ft_strdel(&std->history->current_line);
		std->history->current_line = save_current_command(*edit_line);
		std->history->is_init = true;
	}
	if ((stat->history_index))
	{
		stat->history_index--;
		delete_line(edit_line, stat);
		insert_history(stat, edit_line, history_tab[stat->history_index].data);
	}
}

void		read_history_down(t_line **edit_line, t_line_stat *stat)
{
	t_std			*std;
	t_hist_data		*history_tab;

	std = std_singleton(NULL);
	history_tab = std->history->history_tab;
	if (std->history->nb_hist_line > HIST_SIZE)
		return ;
	if (stat->history_index == std->history->nb_hist_line)
		return ;
	delete_line(edit_line, stat);
	stat->history_index++;
	if (stat->history_index == (std->history->nb_hist_line))
		insert_history(stat, edit_line, std->history->current_line);
	else
		insert_history(stat, edit_line, history_tab[stat->history_index].data);
}
