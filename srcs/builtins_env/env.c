/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 06:41:22 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/17 02:34:02 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	env_list_destroy(void)
{
	t_env *head;
	t_env *prev;

	prev = NULL;
	head = grep_env_head(NULL, false);
	while (head)
	{
		prev = head;
		head = head->next;
		ft_strdel(&prev->name);
		ft_strdel(&prev->value);
		free(prev);
	}
	std_singleton(NULL)->nb_env = 0;
	grep_env_head(NULL, true);
}

void	env_del(char *name)
{
	t_env	*prev;
	t_env	*head;

	head = grep_env_head(NULL, false);
	prev = NULL;
	while (head)
	{
		if (ft_strcmp(head->name, name) == 0)
		{
			if (!prev)
				grep_env_head(head->next, true);
			else
				prev->next = head->next;
			ft_strdel(&head->name);
			if (head->value)
				ft_strdel(&head->value);
			free(head);
			std_singleton(NULL)->nb_env--;
		}
		prev = head;
		head = head->next;
	}
}

void	recupath(void)
{
	t_env	*tmp;
	t_std	*std;

	tmp = NULL;
	std = std_singleton(NULL);
	if (std->path)
		array_free(&(std_singleton(NULL)->path));
	if ((tmp = env_search("PATH")) && tmp->value)
	{
		if (!(std->path = (ft_strsplit(tmp->value, ':'))))
		{
			ft_strdel(&tmp->value);
			ft_fatalexit("split error");
		}
	}
}

void	add_env(char *name, char *value)
{
	t_env	*new;
	t_std	*std;

	new = NULL;
	std = std_singleton(NULL);
	std->nb_env++;
	if ((new = env_search(name)))
	{
		if (new->value)
			ft_strdel(&new->value);
		if (value)
			new->value = ft_strdup(value);
	}
	else
	{
		if (!(new = malloc(sizeof(t_env))))
			exit(-1);
		new->next = NULL;
		if (!(new->name = ft_strdup(name)))
			ft_fatalexit("strdup in add_env");
		new->value = (value) ? ft_strdup(value) : NULL;
		add_right(new);
	}
}
