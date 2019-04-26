/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 04:54:03 by mmeziyan          #+#    #+#             */
/*   Updated: 2019/04/12 20:38:35 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_ast	*left_son_pipe(t_lexer *lexer, int pfd[2], t_ast *new)
{
	close(pfd[0]);
	dup2(pfd[1], 1);
	close(pfd[1]);
	if (!(new->left = process(lexer, new, 3)))
	{
		ft_puterror("syntax error: unexpected '|'");
		new->ret = -1;
	}
	return (new);
}

static void		right_father_pipe(t_lexer *lexer, int pfd[2], t_ast *new)
{
	close(pfd[1]);
	dup2(pfd[0], 0);
	close(pfd[0]);
	if (!(new->right = process(lexer, new, 4)))
		ft_fatalexit("syntax error: unexpected '|'");
	free_ast(&new);
	free_lexer(&std_singleton(NULL)->lexer);
	exit(0);
}

static t_ast	*pipe_fork(t_lexer *lexer, int pfd[2], t_ast *new)
{
	pid_t	pid;
	int		status;
	int		tmp;
	int		ret;

	ret = 0;
	tmp = -1;
	status = 0;
	if ((pid = fork()) < 0)
		ft_fatalexit("fork failed");
	tmp = dup(1);
	if (pid == 0)
		right_father_pipe(lexer, pfd, new);
	new = left_son_pipe(lexer, pfd, new);
	dup2(tmp, 1);
	close(tmp);
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	if (WIFEXITED(status))
		new->ret = WEXITSTATUS(status);
	return (new);
}

t_ast			*ft_pipe(t_lexer *lexer, t_ast *dad, t_lexer *new_separator)
{
	t_ast	*new;
	int		pfd[2];

	if (pipe(pfd) == -1)
		ft_fatalexit("pipe failed");
	if (!(new = new_node(new_separator, dad)))
		ft_fatalexit("Malloc in separator_pipe");
	new = pipe_fork(lexer, pfd, new);
	return (new);
}
