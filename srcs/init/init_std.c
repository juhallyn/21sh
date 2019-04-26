/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_std.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:29:12 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 12:45:48 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_std	*std_singleton(t_std *std)
{
	static t_std	*std_stat;

	if (std)
		std_stat = std;
	return (std_stat);
}

void	init_std(t_std **std)
{
	extern char	**environ;

	if (!(*std = (t_std*)ft_memalloc(sizeof(t_std))))
		ft_fatalexit("can't allocate std in init_std");
	(*std)->history = NULL;
	(*std)->lexer = NULL;
	(*std)->line = NULL;
	(*std)->ast = NULL;
	(*std)->ret = 0;
	(*std)->exec = false;
	(*std)->eof_str = NULL;
	(*std)->term = false;
	(*std)->command_line = NULL;
	(*std)->heredoc_line = NULL;
	(*std)->heredoc_list = NULL;
	(*std)->clipboard = NULL;
	(*std)->term = true;
	(*std)->test = 0;
	std_singleton(*std);
	if (isatty(0))
		(*std)->history = init_history();
}
