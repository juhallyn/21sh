/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:32:45 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/14 05:56:52 by hp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static inline void	free_(char *command, t_line **edit_line, bool free)
{
	if (command)
		ft_strdel(&command);
	if (free)
		free_list(edit_line, free);
}

static inline int	parse_newline(int c)
{
	if (c == NEWLINE_ANSI)
		return ('\032');
	else if (c == '\n')
		return ('J');
	else
		return (c);
}

char				*list_to_str(t_line **edit_line, bool free)
{
	char		*command;
	size_t		i;
	t_line		*tmp;

	i = 0;
	tmp = *edit_line;
	command = malloc_str(*edit_line);
	if (tmp && tmp->next)
		tmp = tmp->next;
	else
	{
		free_(command, edit_line, free);
		return (NULL);
	}
	while (tmp)
	{
		command[i] = parse_newline(tmp->c);
		tmp = tmp->next;
		i++;
	}
	command[i] = '\0';
	free_(NULL, edit_line, free);
	return (command);
}

void				read_err_free(t_line_stat **stat)
{
	free(*stat);
	ft_fatalexit("read fail");
}

void				reset_stat(t_line_stat **stat, int prompt_mode)
{
	(*stat)->cursor_index = 0;
	(*stat)->focus_line = 1;
	(*stat)->insert_line = 1;
	(*stat)->nb_char = 0;
	(*stat)->nb_line = 1;
	(*stat)->prompt_mode = prompt_mode;
	if (prompt_mode == PROMPT_DQUOTE)
		(*stat)->prompt_size = 8;
	else if (prompt_mode == PROMPT_HEREDOC)
		(*stat)->prompt_size = 9;
	else
		(*stat)->prompt_size = 7;
}
