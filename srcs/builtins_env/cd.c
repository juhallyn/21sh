/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 08:02:53 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/16 05:41:58 by hp               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		translate_1(char **tab, char **new)
{
	char	*tmp;
	int		pos;
	int		n;

	n = -1;
	while (tab[++n])
	{
		if (ft_strcmp(tab[n], "..\0") == 0)
		{
			tmp = *new;
			pos = last_occurence(tmp, '/');
			*new = (pos == 0) ? ft_strdup("/") : ft_strndup(*new, pos);
			ft_strdel(&tmp);
		}
		else if (ft_strcmp(tab[n], ".\0") == 0)
			continue ;
		else
		{
			tmp = *new;
			*new = (new[0][1]) ? ft_strjoins(3, *new, "/", tab[n]) :
				ft_strjoin(*new, tab[n]);
			ft_strdel(&tmp);
		}
	}
}

static char		*translate(char *str)
{
	char	*new;
	char	**tab;
	char	cwd[4096];

	if (str[0] != '/' && getcwd(cwd, sizeof(cwd)))
		new = ft_strdup(cwd);
	else
		new = ft_strdup("/");
	tab = ft_strsplit(str, '/');
	translate_1(tab, &new);
	free_tab(&tab);
	return (new);
}

static int		move_to(char *dest)
{
	char	cwd[4096];
	char	*clean;
	int		ret;

	ret = 0;
	getcwd(cwd, sizeof(cwd));
	if (chdir((clean = translate(dest))) == 0)
	{
		if (cwd[0])
			add_env("OLDPWD", cwd);
		add_env("PWD", clean);
	}
	else
	{
		ret = -1;
		my_printf("21sh : cd: '%s': ", 2, dest);
		if ((ret = access(dest, F_OK)) == -1)
			ft_putstr_fd("no such file or directory\n", 2);
		else if ((ret = access(dest, R_OK)) == -1)
			ft_putstr_fd("permission denied\n", 2);
		else
			ft_putstr_fd("not a directory\n", 2);
	}
	ft_strdel(&clean);
	return (ret == -1 ? -1 : 0);
}

int				buil_cd(t_ast *ast)
{
	t_env	*tmp;

	if (ft_strcmp(ast->argv[0], "cd\0") != 0)
		return (0);
	if (ast->argv[1] && ast->argv[2])
	{
		my_printf("cd: too many arguments\n", 2);
		return ((ast->ret = -1));
	}
	if (!(tmp = env_search("HOME")) && !ast->argv[1])
	{
		my_printf("cd: HOME not set\n", 2);
		return ((ast->ret = -1));
	}
	if (tmp && !ast->argv[1])
		ast->ret = move_to(tmp->value);
	if (ast->argv[1])
	{
		if (ast->argv[1][0] == '-' && !ast->argv[1][1])
			(tmp = env_search("OLDPWD")) ? move_to(tmp->value) :
				my_printf("cd: OLDPWD not set\n", 2);
		else
			ast->ret = move_to(ast->argv[1]);
	}
	return (1);
}
