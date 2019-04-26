/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 08:12:34 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 08:12:37 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*line_editing(int cmd_return)
{
	t_std	*std;
	char	*command;

	command = NULL;
	std = std_singleton(NULL);
	std->line = init_line('\0');
	std->stat = init_line_stat();
	print_prompt(cmd_return, PROMPT_STANDARD, \
	std_singleton(NULL)->win.ws_col - PROMPT_SIZE);
	command = readline(&std->line);
	if (command != NULL)
		return (command);
	return (NULL);
}

static char		*readline_process(t_line **edit_line, t_line_stat **stat)
{
	char			str_key[9];
	int				prompt_mode;
	int				key;

	while (42)
	{
		ft_bzero(&str_key, 9);
		if (read(0, str_key, 8) > 0)
		{
			key = 0;
			key = ft_atoi_mod(str_key);
			paste_mod(str_key, edit_line, *stat);
			if ((prompt_mode = ft_edit_line(edit_line, *stat, key)) == -1)
				return (NULL);
			if (write_prompt(prompt_mode) == PROMPT_STANDARD)
				return (std_singleton(NULL)->command_line);
		}
		else
			read_err_free(stat);
	}
	return (std_singleton(NULL)->command_line);
}

char			*readline(t_line **edit_line)
{
	char			*command;
	t_std			*std;

	std = std_singleton(NULL);
	command = readline_process(edit_line, &std->stat);
	free(std->stat);
	std->stat = NULL;
	return (command);
}
