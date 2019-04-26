/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:29:31 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 03:42:07 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_quit_env(t_env *erase)
{
	free(erase);
	env_list_destroy();
	free(std_singleton(NULL));
	ft_fatalexit("Malloc : init_env");
}

void		init_env(void)
{
	extern char	**environ;
	int			n;
	char		*ptr;
	t_env		*new;

	n = -1;
	while (environ[++n])
	{
		if (!(ptr = ft_strchr(environ[n], '=')))
			continue ;
		if (!(new = malloc(sizeof(t_env))))
			exit(-1);
		new->next = NULL;
		if (!(new->name = ft_strndup(environ[n], ptr - &environ[n][0])))
			ft_quit_env(new);
		if (ft_strcmp(new->name, "SHLVL") == 0 && (ptr + 1))
			new->value = ft_itoa(ft_atoi(ptr + 1) + 1);
		else
			new->value = *(ptr + 1) ? ft_strdup(ptr + 1) : NULL;
		add_right(new);
	}
	if (!env_search("SHLVL") || !env_search("SHLVL")->value)
		add_env("SHLVL", "1");
}
