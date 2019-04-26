/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhallyn <juhallyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:40:55 by juhallyn          #+#    #+#             */
/*   Updated: 2019/04/12 20:42:09 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		fork_exec(t_ast *ast)
{
	t_std	*std;

	std = std_singleton(NULL);
	recupath();
	execute(std, ast, -1);
	struct_redir_destroy();
	env_list_destroy();
	free_ast(&ast);
	free_lexer(&std->lexer);
	exit(-1);
}
