/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 06:49:51 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/16 23:41:02 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				env_option(t_ast *ast, int n)
{
	char	*ptr;
	t_env	env;

	if (ast->argv[n] && ft_strcmp("-i", ast->argv[n]) == 0)
	{
		env_list_destroy();
		std_singleton(NULL)->nb_env = 0;
		n++;
	}
	else if (ast->argv[n] && ft_strncmp("-", ast->argv[n], 1) == 0)
	{
		my_printf("21sh: env: illegal option -- %c\n", 2, ast->argv[n][1]);
		my_printf("env [-i] [name=value]... [utility [argument...]]\n", 2);
		exit(-1);
	}
	while (ast->argv[n] && (ptr = ft_strchr(ast->argv[n], '=')))
	{
		env.name = ft_strndup(ast->argv[n], ptr - ast->argv[n]);
		env.value = *(ptr + 1) ? ft_strdup(ptr + 1) : NULL;
		add_env(env.name, env.value);
		env.name ? ft_strdel(&env.name) : NULL;
		env.value ? ft_strdel(&env.value) : NULL;
		n++;
	}
	return (n);
}

void			env_exec(t_ast *ast, int n)
{
	t_std	*std;
	char	**tmp;

	std = std_singleton(NULL);
	n = env_option(ast, n);
	if (ast->argv[n] && ft_strcmp(ast->argv[n], "env\0") == 0)
		ast->argv[n + 1] ? env_exec(ast, n + 1) : put_env();
	else if (ast->argv[n])
	{
		tmp = ast->argv;
		ast->argv = array_dup(&ast->argv[n]);
		array_free(&tmp);
		if (builtins(ast) == 0)
			exit(ast->ret);
		env_list_to_tab();
		recupath();
		execute(std_singleton(NULL), ast, -1);
		exit(-1);
	}
	else
	{
		put_env();
		exit(0);
	}
}

int				buil_env(t_ast *ast)
{
	pid_t	son;
	int		status;
	int		n;

	n = 0;
	if (ft_strcmp(ast->argv[n++], "env\0") != 0)
		return (0);
	if (!ast->argv[n])
	{
		put_env();
		return (1);
	}
	if ((son = fork()) == -1)
		ft_fatalexit("fork error");
	if (son == 0)
	{
		env_exec(ast, n);
		exit(-1);
	}
	waitpid(son, &status, WUNTRACED | WCONTINUED);
	if (WIFEXITED(status))
		ast->ret = WEXITSTATUS(status);
	return (1);
}

int				buil_unset(t_ast *ast)
{
	int	n;

	n = 0;
	if (ft_strcmp(ast->argv[0], "unsetenv\0") != 0)
		return (0);
	while (ast->argv[++n])
	{
		if (ft_strchr(ast->argv[n], '='))
		{
			my_printf("%sunsetenv: %s: not a valid identifier%s\n"
			, 2, RED, ast->argv[n], RESET);
			ast->ret = -1;
			return ((ast->ret = -1));
		}
		env_del(ast->argv[n]);
	}
	return (1);
}

int				buil_setenv(t_ast *ast)
{
	if (ft_strcmp(ast->argv[0], "setenv\0") != 0)
		return (0);
	if (!ast->argv[1])
		put_env();
	if (ast->argv[1] && ast->argv[2] && ast->argv[3])
	{
		ft_puterror("setenv: too many arguments");
		return ((ast->ret = -1));
	}
	if (ast->argv[1] && ast->argv[2] && !ast->argv[3])
	{
		if (ft_strchr(ast->argv[1], '=') || !ft_isalpha(ast->argv[1][0]))
		{
			my_printf("setenv: '%s': not a valid identifier\n",
			2, ast->argv[1]);
			return ((ast->ret = -1));
		}
		add_env(ast->argv[1], ast->argv[2]);
	}
	else
		return ((ast->ret = -1));
	return (1);
}
