/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 10:31:59 by hp                #+#    #+#             */
/*   Updated: 2018/06/19 20:04:21 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					write_prompt(int prompt_mode)
{
	if (prompt_mode == PROMPT_STANDARD)
		return (PROMPT_STANDARD);
	else if (prompt_mode == PROMPT_ERR)
	{
		print_prompt(-1, PROMPT_STANDARD, std_singleton(NULL)->win.ws_col - 7);
	}
	else if (prompt_mode == PROMPT_QUOTE)
	{
		print_prompt(0, PROMPT_QUOTE, std_singleton(NULL)->win.ws_col - 7);
		return (PROMPT_QUOTE);
	}
	else if (prompt_mode == PROMPT_DQUOTE)
	{
		print_prompt(0, PROMPT_DQUOTE, std_singleton(NULL)->win.ws_col - 8);
		return (PROMPT_DQUOTE);
	}
	else if (prompt_mode == PROMPT_HEREDOC)
	{
		print_prompt(0, PROMPT_HEREDOC, std_singleton(NULL)->win.ws_col - 9);
		return (PROMPT_HEREDOC);
	}
	return (0);
}

static inline int	prompt_err(t_line_stat **stat, t_line **edit_line)
{
	char	*line;

	line = NULL;
	free_list(edit_line, true);
	if (std_singleton(NULL)->command_line)
		ft_strdel(&std_singleton(NULL)->command_line);
	ft_putstr_fd("\n", 0);
	*edit_line = init_line('\0');
	reset_stat(stat, PROMPT_STANDARD);
	init_prompt_size(*stat);
	return (PROMPT_ERR);
}

int					prompt_d_quote(t_line **j_line, t_line_stat **stat,
					t_line **edit_line, int mode)
{
	int		ret_quote;
	t_std	*std;

	std = std_singleton(NULL);
	ret_quote = init_ret_quote(mode, edit_line, j_line);
	if (ret_quote == 0)
	{
		reset_stat(stat, PROMPT_STANDARD);
		if (*j_line && mode != PROMPT_STANDARD)
		{
			std->command_line = list_to_str(j_line, true);
			*j_line = NULL;
		}
		add_to_history(std->command_line, *stat);
		init_prompt_size(*stat);
		return (0);
	}
	if (ret_quote == CHAR_QUOTE || ret_quote == CHAR_DQUOTE)
		return (ret_quote);
	else
		return (0);
}

int					prompt_mode(t_line_stat **stat, t_line **edit_line)
{
	t_std			*std;
	int				mode;
	static t_line	*j_line = NULL;
	int				ret_quote;

	if (!stat && !edit_line && j_line)
		return (-12);
	else if (!stat && !edit_line)
		return (-17);
	std = std_singleton(NULL);
	mode = (*stat)->prompt_mode;
	if ((*stat)->prompt_mode == PROMPT_ERR)
	{
		if (j_line)
			free_list(&j_line, false);
		j_line = NULL;
		return (prompt_err(stat, edit_line));
	}
	if ((ret_quote = prompt_d_quote(&j_line, stat, edit_line, mode)) != 0)
		return (line_d_quote(ret_quote, edit_line, &j_line, stat));
	return (PROMPT_STANDARD);
}

void				init_prompt_size(t_line_stat *stat)
{
	t_std	*std;

	std = std_singleton(NULL);
	if (std->win.ws_col >= stat->prompt_size && stat->prompt_size < 7)
	{
		if (stat->prompt_mode == PROMPT_STANDARD
		|| stat->prompt_mode == PROMPT_QUOTE)
			stat->prompt_size = 7;
		if (stat->prompt_mode == PROMPT_DQUOTE)
			stat->prompt_size = 8;
	}
	if (std->win.ws_col <= stat->prompt_size || (std->win.ws_col == 6)
	|| (std->win.ws_col == 7) || (std->win.ws_col == 8) || std->win.ws_col == 9)
		stat->prompt_size = 0;
}
