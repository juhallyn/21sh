/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_deleting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 18:27:46 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/03/16 22:47:05 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		del_end(t_line **to_del, t_line **prev)
{
	free(*to_del);
	(*to_del) = *prev;
	(*to_del)->next = NULL;
}

static void		del_head(t_line **to_del, t_line **next)
{
	free(*to_del);
	(*to_del) = *next;
	(*to_del)->prev = NULL;
}

static void		del_curent(t_line **to_del)
{
	free(*to_del);
	*to_del = NULL;
}

static void		del_middle(t_line **prev, t_line **to_del, t_line **next)
{
	(*prev)->next = *next;
	(*next)->prev = *prev;
	del_curent(to_del);
	(*to_del) = *prev;
}

void			delete_char(t_line **to_del)
{
	t_line	*prev;
	t_line	*next;

	prev = NULL;
	next = NULL;
	if (!(*to_del))
		return ;
	if ((*to_del)->prev)
		prev = (*to_del)->prev;
	if ((*to_del)->next)
		next = (*to_del)->next;
	if (prev && next)
		del_middle(&prev, to_del, &next);
	if (!prev && next)
		del_head(to_del, &next);
	if (prev && !next)
		del_end(to_del, &prev);
	if (!prev && !next)
		del_curent(to_del);
}
