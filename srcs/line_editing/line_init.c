/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 16:07:52 by mmeziyan          #+#    #+#             */
/*   Updated: 2019/04/12 20:22:52 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			print_prompt(int cmd_return, int prompt_mode, int size)
{
	if (prompt_mode == PROMPT_STANDARD)
	{
		ft_put_termcap("dl");
		ft_put_termcap("cr");
		my_printf("%s21sh %sᐅ%s ", 0, CYN, cmd_return == 0 ? GRN : RED, RESET);
	}
	else if (prompt_mode == PROMPT_QUOTE)
		ft_putstr_fd("\nquoteᐅ ", 0);
	else if (prompt_mode == PROMPT_DQUOTE)
		ft_putstr_fd("\ndquoteᐅ ", 0);
	else if (prompt_mode == PROMPT_HEREDOC)
		ft_putstr_fd("heredocᐅ ", 0);
	if (size < 7)
		ft_putstr_fd("\n↴\n", 0);
}

t_line			*malloc_line_node(void)
{
	t_line	*edit_line;

	edit_line = NULL;
	edit_line = (t_line*)malloc(sizeof(*edit_line));
	if (!edit_line)
		ft_fatalexit("allocation fail : edit_line struct");
	edit_line->next = NULL;
	edit_line->prev = NULL;
	return (edit_line);
}

t_line_stat		*init_line_stat(void)
{
	t_line_stat		*stat;

	stat = NULL;
	stat = (t_line_stat*)malloc(sizeof(*stat));
	if (!stat)
		ft_fatalexit("allocation fail : stat (readline)");
	stat->cursor_index = 0;
	stat->history_index = std_singleton(NULL)->history->nb_hist_line;
	stat->prompt_size = 7;
	init_prompt_size(stat);
	stat->win_index = stat->prompt_size + stat->cursor_index;
	stat->focus_line = 1;
	stat->nb_line = 1;
	stat->insert_line = 1;
	stat->nb_char = 0;
	stat->prompt_mode = PROMPT_STANDARD;
	stat->visual_select = false;
	return (stat);
}

t_line			*init_line(int key)
{
	t_line	*edit_line;

	edit_line = malloc_line_node();
	edit_line->c = key;
	edit_line->next = NULL;
	edit_line->prev = NULL;
	return (edit_line);
}
