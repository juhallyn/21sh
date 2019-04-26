/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 05:33:36 by mmeziyan          #+#    #+#             */
/*   Updated: 2019/04/13 16:00:07 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				right(const char *path)
{
	struct stat	sta;

	lstat(path, &sta);
	if (sta.st_mode & S_IXUSR)
		return (1);
	return (0);
}

int				execute(t_std *std, t_ast *ast, int n)
{
	char	*prog;

	prog = NULL;
	if ((ft_strncmp(ast->argv[0], "./", 2) == 0 || ast->argv[0][0] == '/' \
	|| ft_strncmp(ast->argv[0], "../", 3) == 0) \
	&& access(ast->argv[0], X_OK) == 0)
		execve(ast->argv[0], ast->argv, std->myenv);
	while (std->path && std->path[++n])
	{
		prog = ft_strjoins(3, std->path[n], "/", ast->argv[0]);
		if (access(prog, X_OK) == 0)
			execve((const char *)prog, ast->argv, std->myenv);
		if (access(prog, F_OK) == 0 && !right(prog))
		{
			ft_strdel(&prog);
			my_printf("21sh: permission denied: %s\n", 2, ast->argv[0]);
			return ((ast->ret = -1));
		}
		ft_strdel(&prog);
	}
	if (access(ast->argv[0], F_OK) == 0 && !right(ast->argv[0]))
		my_printf("21sh: permission denied: %s\n", 2, ast->argv[0]);
	else
		my_printf("21sh: command not found: %s\n", 2, ast->argv[0]);
	return ((ast->ret = -1));
}

char			**cmd_create(t_lexer *lexer_node)
{
	char	**cmd;
	t_lexer *lexer_tmp;
	int		n;

	n = 0;
	lexer_tmp = lexer_node;
	while (lexer_tmp && lexer_tmp->status != 1)
	{
		if (lexer_tmp->type == WORD && lexer_tmp->status != 2)
			n++;
		lexer_tmp = lexer_tmp->next;
	}
	if (!(cmd = ft_memalloc(sizeof(char *) * (n + 1))))
		ft_fatalexit("Malloc : cmd_create");
	cmd[n] = NULL;
	n = -1;
	while (lexer_node && (lexer_node->status != 1))
	{
		if (lexer_node->type == WORD && lexer_node->status != 2)
			if (!(cmd[++n] = ft_strdup(lexer_node->data)))
				ft_fatalexit("Malloc : cmd_create");
		lexer_node = lexer_node->next;
	}
	return (cmd);
}

static int		exec_plus(t_ast *ast, pid_t son)
{
	t_std	*std;
	int		status;

	status = 0;
	std = std_singleton(NULL);
	std->forked = true;
	waitpid(son, &status, WUNTRACED | WCONTINUED);
	array_free(&std->myenv);
	struct_redir_destroy();
	if (WIFEXITED(status))
		if ((ast->ret = WEXITSTATUS(status)) != 0 && std->stdin)
			exit(-1);
	std->forked = false;
	return (ast->ret);
}

int				exec(t_ast *ast)
{
	t_std	*std;
	pid_t	son;

	std = std_singleton(NULL);
	std->exec = true;
	do_redir();
	if (builtins(ast) == 0)
		return (ast->ret);
	env_list_to_tab();
	if ((son = fork()) == -1)
		ft_fatalexit("fork error");
	if (son == 0)
		fork_exec(ast);
	else
		return (exec_plus(ast, son));
	return (-1);
}
