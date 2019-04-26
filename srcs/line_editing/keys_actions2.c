/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:50:19 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 20:12:47 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				newline_eof(t_line **edit_line, t_line_stat *stat, int key)
{
	t_std	*std;
	int		ret_quote;

	ret_quote = 0;
	std = std_singleton(NULL);
	move_end(*edit_line, stat);
	if (std->eof_str)
	{
		(key != CTRL_D) ? ft_putchar_fd('\n', 0) : NULL;
		if (((std->heredoc_line = list_to_str(edit_line, true))
		&& (ft_strcmp(std->heredoc_line, std->eof_str) == 0)) || key == CTRL_D)
		{
			ft_strdel(&std->heredoc_line);
			std->heredoc_line = list_to_str(&std->heredoc_list, true);
			std->eof_str = NULL;
			reset_stat(&std->stat, PROMPT_STANDARD);
			return (PROMPT_STANDARD);
		}
		join_line(std->heredoc_line, &std->heredoc_list);
		ft_strdel(&std->heredoc_line);
		*edit_line = init_line('\0');
		reset_stat(&std->stat, PROMPT_HEREDOC);
		return (PROMPT_HEREDOC);
	}
	return (prompt_mode(&stat, edit_line));
}

int				error_key(t_line **edit_line, t_line_stat *stat, int key)
{
	t_std	*std;

	std = std_singleton(NULL);
	if (std->eof_str)
	{
		free_list(edit_line, NULL);
		ft_putchar_fd('\n', 0);
		std->eof_str = NULL;
		reset_stat(&std->stat, PROMPT_ERR);
		return (newline_eof(edit_line, stat, key));
	}
	move_end(*edit_line, stat);
	stat->prompt_mode = PROMPT_ERR;
	return (prompt_mode(&stat, edit_line));
}
