/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:13:36 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 20:12:37 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**					Errors
**	--	put an error on STDERR before quit --
*/

void				ft_fatalexit(char *error)
{
	if (error)
		my_printf("%sError : %s%s\nexit\n", 2, RED, error, RESET);
	exit(-1);
}

void				ft_puterror(char *error)
{
	if (error)
		my_printf("%sError : %s%s\n", 2, RED, error, RESET);
	if (std_singleton(NULL)->stdin)
		exit(-1);
}

/*
**				ft_atoi_mod
**	--	to convert string to one int value --
*/

void				ft_put_termcap(char *termcap)
{
	ft_putstr_fd(tgetstr(termcap, NULL), 0);
}

int					parse_error_near(char *err_data)
{
	my_printf("%sError : parse error near `%s`%s\n", 2, RED, err_data, RESET);
	return (-1);
}

void				lexer_clean_redir(t_lexer *cmd)
{
	while (cmd && cmd->status != 1)
	{
		if (cmd->type == REDIR_SUP || cmd->type == D_REDIR_SUP
		|| cmd->type == REDIR_INF || cmd->type == D_REDIR_INF)
		{
			cmd->status = 2;
			if (cmd->prev && (cmd->prev->type == STD_SEPARATOR
			|| cmd->prev->type == IO_NUMBER))
				cmd->prev->status = 2;
			if (cmd->next && cmd->next->type == AMPERSAND)
			{
				cmd = cmd->next;
				cmd->status = 2;
			}
			if (cmd->next && cmd->next->type == STD_SEPARATOR)
			{
				cmd = cmd->next;
				cmd->status = 2;
			}
			if (cmd->next && cmd->next->type == WORD)
				cmd->next->status = 2;
		}
		cmd = cmd->next;
	}
}
