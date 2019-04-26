/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:30:50 by mmeziyan          #+#    #+#             */
/*   Updated: 2019/04/12 19:06:06 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGWINCH, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	signal_handler(int sig)
{
	t_std *std;

	std = std_singleton(NULL);
	if (sig == SIGQUIT && std->exec)
		my_printf("\n%s---%sQuit%s---%s\n", 2, RED, RESET, RED, RESET);
	if (sig == SIGTSTP && std->exec)
		my_printf("\n%s--%sNo job control%s--%s\n", 2, RED, RESET, RED, RESET);
	if (sig == SIGINT)
	{
		if (!std->exec && !std->stdin)
			ioctl(0, TIOCSTI, "\5\0");
		else if (std_singleton(NULL)->forked == false)
			ft_putchar_fd('\n', 0);
	}
	if (sig == SIGWINCH)
		ioctl(0, TIOCSTI, "\2\0");
}
