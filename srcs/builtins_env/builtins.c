/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 06:41:22 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/17 02:34:02 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		buil_echo(t_ast *ast)
{
	int	n;

	n = 0;
	if (ft_strcmp(ast->argv[0], "echo\0") != 0)
		return (0);
	if (!ast->argv[1])
		ft_putendl("");
	while (ast->argv[++n])
	{
		ft_putstr(ast->argv[n]);
		ast->argv[n + 1] ? ft_putchar(' ') : ft_putchar('\n');
	}
	return (1);
}

int		buil_exit(t_ast *ast)
{
	char	*ptr;

	ptr = NULL;
	if (ft_strcmp(ast->argv[0], "exit\0") != 0)
		return (0);
	if (ast->argv[1] && ast->argv[2])
	{
		my_printf("exit: too many arguments\n", 2);
		ast->ret = -1;
		ast->ret = -1;
		return (-1);
	}
	my_printf("exit\n", 1);
	if (ast->argv[1])
	{
		if ((ptr = ft_just_num(ast->argv[1])))
		{
			my_printf("exit: '%s': numeric argument required\n", 2, ptr);
			exit(-1);
		}
		exit(ft_atoi(ast->argv[1]));
	}
	if (!ast->argv[1])
		exit(ast->ret);
	return (1);
}

int		buil_pwd(t_ast *ast)
{
	char	cwd[1024];

	if (ft_strcmp(ast->argv[0], "pwd\0") != 0)
		return (0);
	if ((getcwd(cwd, sizeof(cwd))))
		ft_putendl(cwd);
	else
	{
		ft_putendl_fd("pwd: .: No such file or directory\n", 2);
		ast->ret = -1;
	}
	return (1);
}

int		buil_clear(t_ast *ast)
{
	if (ft_strcmp(ast->argv[0], "clear\0") != 0)
		return (0);
	ft_put_termcap(CLEAR);
	return (1);
}

int		builtins(t_ast *ast)
{
	int	n;

	n = 1;
	n = buil_exit(ast) ? 0 : n;
	n = buil_cd(ast) ? 0 : n;
	n = buil_setenv(ast) ? 0 : n;
	n = buil_unset(ast) ? 0 : n;
	n = buil_echo(ast) ? 0 : n;
	n = buil_env(ast) ? 0 : n;
	n = buil_clear(ast) ? 0 : n;
	n = buil_pwd(ast) ? 0 : n;
	return (n);
}
