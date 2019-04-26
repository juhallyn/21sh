/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 08:10:33 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/17 03:52:36 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void				history_char_check(char *data)
{
	size_t		i;

	i = 0;
	while (data[i])
	{
		if (ft_ischar(data[i]) == 0 && data[i] != '\032')
			ft_fatalexit("Fatal error : conrupt history file");
		i++;
	}
}

void					add_end_history(t_hist_data **history_list, char *data)
{
	t_hist_data			*node;
	t_hist_data			*tmp;

	node = NULL;
	node = (t_hist_data*)malloc(sizeof(*node));
	if (!node)
		ft_putendl("node allocation fail");
	history_char_check(data);
	node->data = ft_strdup(data);
	node->next = NULL;
	if (!*history_list)
	{
		*history_list = node;
		return ;
	}
	tmp = *history_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_hist_data				*fill_history_list(t_history *history)
{
	t_hist_data	*history_list;
	char		*line;
	int			ret;

	history_list = NULL;
	line = NULL;
	ret = 0;
	history->nb_hist_line = 0;
	while ((ret = get_next_line(history->history_fd, &line) > 0))
	{
		add_end_history(&history_list, line);
		ft_strdel(&line);
		history->nb_hist_line++;
	}
	if (ret == -1)
		ft_puterror("History : read fail");
	return (history_list);
}

t_hist_data				*reference_list(t_history *history)
{
	t_hist_data				*history_tab;
	t_hist_data				*history_list;
	size_t					i;

	i = 0;
	if (!history->nb_hist_line)
		return (NULL);
	history_tab = (t_hist_data*)malloc(sizeof(*history_tab) * HIST_SIZE);
	if (!history_tab)
		ft_fatalexit("allocation of history_tab fail");
	history_list = history->history_list;
	if (history->nb_hist_line >= HIST_SIZE)
	{
		ft_puterror("--> History file to long,\nshell run without history");
		return (NULL);
	}
	while ((i < history->nb_hist_line) && history_list && i < (HIST_SIZE - 1))
	{
		(history_tab[i]).data = history_list->data;
		history_list = history_list->next;
		i++;
	}
	return (history_tab);
}
