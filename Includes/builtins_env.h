/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:32:25 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 08:29:59 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_ENV_H
# define BUILTINS_ENV_H

# include "shell.h"

/*
**  ----------------------------------------------------------------------------
**							--	STRUCTS --
**  ----------------------------------------------------------------------------
*/

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

/*
**  ----------------------------------------------------------------------------
**							--	FUNCTIONS --
**  ----------------------------------------------------------------------------
*/

/*
**	--	init_env.c --
*/

void				init_env(void);

/*
**	--	env.c --
*/

void				env_list_destroy(void);
void				env_del(char *name);
void				recupath();
void				add_env(char *name, char *value);

/*
**	--	env_tools.c --
*/

t_env				*grep_env_head(t_env *new, bool replace);
void				add_right(t_env *new);
t_env				*env_search(char *name);
void				env_list_to_tab(void);
void				put_env(void);

/*
**	--	builtins.c --
*/

int					builtins(t_ast *ast);
int					buil_echo(t_ast *ast);
int					buil_exit(t_ast *ast);

/*
**	--	cd.c --
*/

int					buil_cd(t_ast *ast);

/*
**	--	buil_env.c --
*/

int					buil_env(t_ast *ast);
int					buil_unset(t_ast *ast);
int					buil_setenv(t_ast *ast);

#endif
