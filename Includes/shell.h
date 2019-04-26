/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:32:45 by mmeziyan          #+#    #+#             */
/*   Updated: 2019/04/12 18:51:45 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <termios.h>
# include <termcap.h>
# include <stdio.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "libft.h"
# include "line_editing.h"
# include "lexer.h"
# include "ast.h"
# include "builtins_env.h"

/*
**  ----------------------------------------------------------------------------
**							--	STRUCTS --
**  ----------------------------------------------------------------------------
*/

/*
**	--			Master_stuct		--
**					(t_std)
*/

typedef struct		s_std
{
	bool				forked;
	struct winsize		win;
	struct s_history	*history;
	char				*clipboard;
	char				**path;
	struct s_lexer		*lexer;
	struct s_ast		*ast;
	struct s_line_stat	*stat;
	char				*tmp_argv;
	bool				exec;
	bool				stdin;
	bool				term;
	bool				fork_pipe;
	struct s_line		*line;
	char				*command_line;
	struct s_line		*heredoc_list;
	char				*heredoc_line;
	char				*eof_str;
	char				**myenv;
	int					nb_env;
	int					ret;
	int					test;
}					t_std;

/*
**  ----------------------------------------------------------------------------
**							--	FUNCTIONS --
**  ----------------------------------------------------------------------------
*/

/*
**	--	init_std.c --
*/

t_std				*std_singleton(t_std *std);
void				init_std(t_std **std);

/*
**	--	exec.c --
*/

int					execute_cmd(char *command);
int					execute(t_std *std, t_ast *ast, int n);

/*
**	--	term.c --
*/

int					init_term_canon(bool b_canon);

/*
**	--	tools3.c --
*/

char				*create_tmp_file(void);
void				i_exp(char **s1, char **s2, char **s3, char **s4);

/*
**	--	tools2.c --
*/

char				*ft_justnum(char *str);
int					ft_ischar(int key);
int					is_nb(char *nbr);
size_t				ft_power(int n, int p);
int					ft_atoi_mod(char *str);

/*
**	--	tools2.c --
*/

void				ft_fatalexit(char *error);
void				ft_puterror(char *error);
void				ft_put_termcap(char *termcap);
int					parse_error_near(char *err_data);
void				lexer_clean_redir(t_lexer *cmd);

/*
**	--	signal.c --
*/

void				ft_signal(void);
void				signal_handler(int sig);

/*
**  ----------------------------------------------------------------------------
**							--	EXPANSION --
**  ----------------------------------------------------------------------------
*/

/*
**	--	signal.c --
*/

t_lexer				*expand_quoted_string(t_lexer *node);
void				expand(t_lexer **lexer);

#endif
