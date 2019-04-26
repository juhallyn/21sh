/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 08:04:05 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 08:04:13 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env	*grep_env_head(t_env *new, bool replace)
{
	static t_env *head = NULL;

	if (replace)
		head = new;
	return (head);
}

void	put_env(void)
{
	t_env *head;

	head = grep_env_head(NULL, false);
	while (head)
	{
		my_printf("%s=%s\n", 1, head->name, head->value);
		head = head->next;
	}
}

void	add_right(t_env *new)
{
	t_env *head;

	std_singleton(NULL)->nb_env++;
	head = grep_env_head(NULL, false);
	if (!head)
	{
		grep_env_head(new, true);
		return ;
	}
	while (head->next)
		head = head->next;
	head->next = new;
}

t_env	*env_search(char *name)
{
	t_env	*head;

	head = grep_env_head(NULL, false);
	while (head)
	{
		if (ft_strcmp(head->name, name) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void	env_list_to_tab(void)
{
	int		n;
	t_env	*head;
	t_std	*std;

	std = std_singleton(NULL);
	head = grep_env_head(NULL, false);
	n = -1;
	if (!(std->myenv = (char **)malloc(sizeof(char *) * (std->nb_env + 1))))
		ft_fatalexit("Malloc : env_tools");
	while (head)
	{
		if (!(std->myenv[++n] =
		ft_strjoins(3, head->name, "=", head->value ? head->value : "")))
			ft_fatalexit("Strjoins : env_tools");
		head = head->next;
	}
	std->myenv[n + 1] = NULL;
}
