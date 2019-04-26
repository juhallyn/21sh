/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:41:51 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 04:30:48 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		replace_fd(t_redir *prev, t_redir *head, t_redir data)
{
	t_redir		*new;

	new = new_redir_node(data);
	if (head->fd_in > 2)
		close(head->fd_in);
	free(head);
	if (prev == NULL)
	{
		if (head->next)
		{
			head = grep_head(head->next, true);
			head->next = new;
		}
		else
			grep_head(new, true);
	}
	else
		prev->next = new;
}

int			to_replace_fd(t_redir data)
{
	t_redir		*head;
	t_redir		*prev;

	head = grep_head(NULL, false);
	prev = NULL;
	while (42)
	{
		if (head->fd_out == data.fd_out && data.fd_out > 0)
		{
			replace_fd(prev, head, data);
			return (1);
		}
		if (!head->next)
		{
			head->next = new_redir_node(data);
			return (1);
		}
		prev = head;
		head = head->next;
	}
	return (0);
}

static void	ft_out_cpy(void)
{
	t_redir		*head;

	head = grep_head(NULL, false);
	while (head)
	{
		head->fd_out_cpy = dup(head->fd_out);
		head = head->next;
	}
}

void		do_redir(void)
{
	t_redir		*head;

	ft_out_cpy();
	head = grep_head(NULL, false);
	while (head)
	{
		if (head->fd_out == -2)
		{
			head = head->next;
			continue ;
		}
		if (head && head->fd_out == -1)
		{
			my_printf("21sh : %i: Bad file descriptor\n", 2, head->fd_out);
			return ;
		}
		dup2(head->fd_in, head->fd_out);
		if (head->fd_in > 2)
			close(head->fd_in);
		head = head->next;
	}
}
