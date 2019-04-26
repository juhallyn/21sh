/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 08:10:38 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 12:51:27 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static inline char	*path_history(void)
{
	char	*home;
	char	*path;

	home = getenv("HOME");
	if (!home)
	{
		ft_puterror("$HOME not define, shell run without history");
		return (NULL);
	}
	path = ft_strjoin(home, "/.21sh_history");
	if (!path)
	{
		ft_puterror("join failed, shell run without history");
		return (NULL);
	}
	return (path);
}

int					init_history_fd(void)
{
	int		fd;
	char	*path;

	fd = -1;
	path = path_history();
	if (!path)
		return (-1);
	fd = open(path, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
	ft_strdel(&path);
	if (fd < 0)
	{
		ft_puterror("open fd failed, shell run without history");
		return (-1);
	}
	return (fd);
}

t_history			*init_history(void)
{
	t_history		*history;

	history = NULL;
	history = (t_history*)malloc(sizeof(*history));
	if (!history)
		ft_fatalexit("allocation fail : history struct");
	history->nb_hist_line = 0;
	history->current_line = NULL;
	history->is_init = false;
	history->history_fd = init_history_fd();
	history->history_list = fill_history_list(history);
	history->history_tab = reference_list(history);
	return (history);
}
