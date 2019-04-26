/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:46:48 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 06:57:51 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_redir	*grep_head(t_redir *new, bool replace)
{
	static t_redir *head = NULL;

	if (replace)
		head = new;
	return (head);
}

void	struct_redir_destroy(void)
{
	t_redir *to_destroy;
	t_redir *tmp;
	t_std	*std;

	std = std_singleton(NULL);
	to_destroy = grep_head(NULL, false);
	while (to_destroy)
	{
		tmp = to_destroy;
		to_destroy = to_destroy->next;
		dup2(tmp->fd_out_cpy, tmp->fd_out);
		close(tmp->fd_out_cpy);
		free(tmp);
	}
	grep_head(NULL, true);
}

t_redir	*new_redir_node(t_redir data)
{
	t_redir *new;

	if (!(new = malloc(sizeof(t_redir))))
		ft_fatalexit("malloc error");
	new->fd_out = data.fd_out;
	new->redir_type = data.redir_type;
	new->fd_in = data.fd_in;
	new->io_number = data.io_number;
	new->fd_out_cpy = -1;
	new->next = NULL;
	return (new);
}

t_lexer	*redir_io_number(t_lexer *cmd, t_redir *redir)
{
	if (cmd->prev && cmd->prev->type == IO_NUMBER
	&& ft_strlen(cmd->prev->data) == 1)
	{
		redir->io_number = ft_atoi(cmd->prev->data);
		if (redir->io_number > 2)
			redir->fd_out = -2;
		else
			redir->fd_out = redir->io_number;
	}
	else
	{
		if (cmd->type == REDIR_INF || cmd->type == D_REDIR_INF)
			redir->fd_out = 0;
		if (cmd->type == REDIR_SUP || cmd->type == D_REDIR_SUP)
			redir->fd_out = 1;
	}
	return (NULL);
}

t_redir	t_redir_init(void)
{
	t_redir redir;

	redir.redir_type = -1;
	redir.fd_in = -1;
	redir.fd_out = -1;
	redir.fd_out_cpy = -1;
	redir.io_number = -1;
	return (redir);
}
