/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:17:43 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 08:11:59 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		eof_key(t_line **edit_line, t_line_stat *stat)
{
	t_std	*std;

	std = std_singleton(NULL);
	if ((*edit_line) && (*edit_line)->next && (*edit_line)->next->c)
		del_delete(stat, edit_line);
	else if (std->eof_str)
	{
		ft_strdel(&std->eof_str);
		reset_stat(&std->stat, PROMPT_STANDARD);
		return (1);
	}
	else if (prompt_mode(NULL, NULL) != -12)
	{
		(std->stdin == false && std->term == true) ?
		init_term_canon(true) : 1;
		ft_putendl_fd("", 0);
		exit(0);
	}
	return (0);
}
