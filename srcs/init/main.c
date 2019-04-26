/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:28:54 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 21:29:00 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static	void	ft_quit_stdin_mode(void)
{
	env_list_destroy();
	free(std_singleton(NULL));
	exit(1);
}

static	void	stdin_mode(t_std *std)
{
	int		ret;

	ret = 0;
	if (!isatty(0))
	{
		std->stdin = true;
		if ((ret = get_next_line(0, &std->command_line)) == -1)
			ft_fatalexit("read fail");
		if (ret == 0)
			ft_quit_stdin_mode();
		if (ret == 1 && !std->command_line[0])
			ft_strdel(&std->command_line);
	}
	else
	{
		if ((ioctl(0, TIOCGWINSZ, &(*std).win) == -1))
			ft_fatalexit("ioctl fail");
		std->stdin = false;
		init_term_canon(false);
		line_editing(std->ret == 0 ? 0 : -1);
		ft_putendl_fd("", 0);
	}
}

static int		command_lexer_parser(void)
{
	t_std	*std;

	std = std_singleton(NULL);
	std->exec = false;
	std->command_line = NULL;
	stdin_mode(std);
	std->ret = 0;
	if (!std->command_line)
		return (1);
	if (std->lexer)
		free_lexer(&std->lexer);
	std->lexer = lexing(std->command_line);
	std->command_line = NULL;
	if (std->lexer == NULL)
		return (1);
	if (!std->stdin)
		init_term_canon(true);
	return (0);
}

int				main(void)
{
	t_std	*std;
	int		ret;

	std = NULL;
	ret = 0;
	init_std(&std);
	init_env();
	ft_signal();
	while (42)
	{
		if ((command_lexer_parser()) == 1)
			continue ;
		if ((std->ast = process(std->lexer, NULL, 0)))
			std->ret = std->ast->ret;
		if (std->ast)
			free_ast(&std->ast);
		std->test = 1;
	}
	return (0);
}
