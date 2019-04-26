/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 18:49:55 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 20:04:54 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				join_line(char *command, t_line **j_line)
{
	size_t		i;

	i = 0;
	if (!*j_line)
		*j_line = init_line('\0');
	if (!command)
	{
		add_end(j_line, NEWLINE_ANSI);
		add_end(j_line, '\n');
		return ;
	}
	else
	{
		while (command[i])
		{
			add_end(j_line, command[i]);
			i++;
		}
	}
	add_end(j_line, NEWLINE_ANSI);
	add_end(j_line, '\n');
}

t_line				*move_list_to_cursor(t_line **edit_line, \
					size_t cursor_index)
{
	t_line	*tmp;
	size_t	i;

	i = 0;
	tmp = *edit_line;
	while (i < (cursor_index) && (tmp))
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

size_t				list_len(t_line *edit_line)
{
	size_t	i;

	i = 0;
	if (!edit_line)
		return (0);
	if (edit_line->next)
		edit_line = edit_line->next;
	else
		return (0);
	while (edit_line)
	{
		edit_line = edit_line->next;
		i++;
	}
	return (i);
}

void				free_list(t_line **edit_line, bool std)
{
	t_line	*tmp;

	tmp = NULL;
	while (*edit_line)
	{
		tmp = (*edit_line)->next;
		free(*edit_line);
		*edit_line = NULL;
		*edit_line = tmp;
	}
	edit_line = NULL;
	if (std)
		std_singleton(NULL)->line = NULL;
}

char				*malloc_str(t_line *edit_line)
{
	char	*command;
	size_t	len;

	len = list_len(edit_line);
	command = ft_strnew(len + 1);
	if (!command)
		ft_fatalexit("allocation error for command in list_to_str");
	return (command);
}
