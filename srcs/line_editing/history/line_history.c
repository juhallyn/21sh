/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 08:10:45 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 08:10:47 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			refresh_tab_history(void)
{
	size_t					i;
	t_std					*std;
	t_hist_data				*history_tab;
	t_hist_data				*history_list;

	i = 0;
	std = std_singleton(NULL);
	history_tab = std->history->history_tab;
	history_list = std->history->history_list;
	if (std->history->nb_hist_line < HIST_SIZE)
		std->history->nb_hist_line++;
	else
		return ;
	while (i < std->history->nb_hist_line && history_list && i < HIST_SIZE)
	{
		(history_tab[i]).data = history_list->data;
		history_list = history_list->next;
		i++;
	}
}

static int			write_in_file(int fd, char *command)
{
	if (write(fd, command, ft_strlen(command)) == -1
	|| (write(fd, "\n", 1)) == -1)
	{
		ft_puterror("While write in history file");
		return (-1);
	}
	return (0);
}

static inline int	write_to_hist_list(t_std *std, t_line_stat *stat,\
					char *command)
{
	if (!std->history->history_list)
	{
		close(std->history->history_fd);
		std->history->history_fd = init_history_fd();
		std->history->history_list = fill_history_list(std->history);
		if (!std->history->history_tab)
			std->history->history_tab = reference_list(std->history);
		stat->history_index = std->history->nb_hist_line;
	}
	else
	{
		add_end_history(&std->history->history_list, command);
		refresh_tab_history();
	}
	return (0);
}

int					add_to_history(char *command, t_line_stat *stat)
{
	t_std			*std;

	std = std_singleton(NULL);
	if (std->history->history_fd < 0 || !command)
		return (-1);
	if (std->history->nb_hist_line >= HIST_SIZE)
	{
		ft_puterror("history is too long, command not saved");
		return (-1);
	}
	if (write_in_file(std->history->history_fd, command) == -1)
		return (-1);
	write_to_hist_list(std, stat, command);
	return (0);
}
