/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:51:00 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 19:44:25 by hp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static	int			search_replace_fd(t_redir data)
{
	t_redir		*head;

	head = grep_head(NULL, false);
	while (head && data.fd_in < -2)
	{
		if (head->io_number == -data.fd_in)
			data.fd_in = head->fd_in;
		head = head->next;
	}
	if (data.fd_in < -2)
		return (-1);
	if (!(head = grep_head(NULL, false)))
	{
		head = new_redir_node(data);
		grep_head(head, true);
		return (1);
	}
	return (to_replace_fd(data));
}

static t_lexer		*redir_word_ampersand(t_lexer *cmd, t_redir *redir)
{
	if (cmd->next && cmd->next->type == WORD)
	{
		cmd = cmd->next;
		if (ft_justnum(cmd->data) || ft_strlen(cmd->data) != 1)
		{
			my_printf("21sh: %s bad file descriptor\n", 2, cmd->data);
			return (NULL);
		}
		else if ((redir->fd_in = ft_atoi(cmd->data)) != redir->fd_out)
		{
			redir->fd_in = redir->fd_in > 2 ? -redir->fd_in : redir->fd_in;
			if ((search_replace_fd(*redir)) == -1)
			{
				my_printf("21sh : %i: Bad file descriptor\n", 2, redir->fd_in);
				struct_redir_destroy();
				return (NULL);
			}
		}
	}
	return (cmd->next ? cmd->next : cmd);
}

static t_lexer		*redir_ampersand(t_lexer *cmd, t_redir *redir)
{
	if (cmd->next && cmd->next->type == STD_SEPARATOR)
		cmd = cmd->next;
	if (!cmd->next)
	{
		my_printf("21sh: syntax error: unexpected 'newline'\n", 2, cmd->data);
		return (NULL);
	}
	if (cmd->next && ft_strcmp(cmd->next->data, "-\0") == 0
	&& cmd->type != REDIR_INF)
	{
		cmd = cmd->next;
		redir->fd_in = open("/dev/null", O_WRONLY);
		search_replace_fd(*redir);
		return (cmd->next ? cmd->next : cmd);
	}
	return (redir_word_ampersand(cmd, redir));
}

static t_lexer		*redirection(t_lexer *cmd)
{
	t_redir		redir;

	redir = t_redir_init();
	redir.redir_type = cmd->type;
	redir_io_number(cmd, &redir);
	if (cmd->next && cmd->next->type == AMPERSAND && cmd->type != D_REDIR_INF)
		return (redir_ampersand(cmd->next, &redir));
	if (cmd->type == D_REDIR_INF)
	{
		redir.fd_in = open(cmd->path_heredoc, O_RDWR);
		ft_strdel(&cmd->path_heredoc);
		search_replace_fd(redir);
		return (cmd);
	}
	if (cmd->next && cmd->next->type == STD_SEPARATOR)
		cmd = cmd->next;
	if ((cmd->next && cmd->next->type == WORD
	&& ft_strcmp(cmd->next->data, "-\0") != 0) && (cmd = cmd->next))
	{
		if ((redir.fd_in =
		ft_creat_file(cmd->data, redir.redir_type, 1)) == -1)
			return (NULL);
	}
	search_replace_fd(redir);
	return (cmd);
}

int					new_redirection(t_lexer *cmd)
{
	t_redir		redir;

	lexer_clean_redir(cmd);
	while (cmd && cmd->status != 1)
	{
		redir = t_redir_init();
		if (cmd->type == REDIR_SUP || cmd->type == D_REDIR_SUP
		|| cmd->type == REDIR_INF || cmd->type == D_REDIR_INF)
			if (!(cmd = redirection(cmd)))
				return (-1);
		cmd = cmd->next;
	}
	return (0);
}
