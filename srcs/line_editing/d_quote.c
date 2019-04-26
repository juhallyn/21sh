/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 08:11:37 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 08:11:40 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		init_ret_quote(int mode, t_line **edit_line, t_line **j_line)
{
	int		ret_quote;
	t_std	*std;

	std = std_singleton(NULL);
	if (mode == PROMPT_STANDARD)
	{
		ret_quote = check_close_d_quote(*edit_line);
		std->command_line = list_to_str(edit_line, true);
		if (*j_line)
			free_list(j_line, false);
	}
	else
	{
		if (std->command_line)
			ft_strdel(&std->command_line);
		std->command_line = list_to_str(edit_line, true);
		join_line(std->command_line, j_line);
		ft_strdel(&std->command_line);
		ret_quote = check_close_d_quote(*j_line);
	}
	return (ret_quote);
}

int		line_d_quote(int ret_quote, t_line **edit_line, t_line **j_line,\
					t_line_stat **stat)
{
	t_std	*std;
	int		prompt;

	prompt = PROMPT_DQUOTE;
	std = std_singleton(NULL);
	if (ret_quote == CHAR_QUOTE)
		prompt = PROMPT_QUOTE;
	reset_stat(stat, prompt);
	*edit_line = init_line('\0');
	if (!*j_line)
		join_line(std->command_line, j_line);
	if (std->command_line)
		ft_strdel(&std->command_line);
	std->command_line = list_to_str(j_line, false);
	std->line = *edit_line;
	init_prompt_size(*stat);
	return (prompt);
}
