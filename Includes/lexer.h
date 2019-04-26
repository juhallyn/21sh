/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:38:50 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 17:25:00 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "shell.h"

/*
**	--	OPERATORS  --
*/

# define TOKEN_SEMICOLON		59
# define TOKEN_REDIR_SUP 		62
# define TOKEN_REDIR_INF 		60
# define TOKEN_PIPE				124
# define TOKEN_WORD				1
# define TOKEN_AMPERSAND		38
# define TOKEN_NEWLINE			10
# define TOKEN_DOLLAR			36

/*
**	--	LEXER --
*/

# define IN_QUOTE				2
# define IN_DQUOTE				1
# define OFF					0

/*
**  ----------------------------------------------------------------------------
**							--	STRUCTS --
**  ----------------------------------------------------------------------------
*/

typedef enum			e_token
{
	T_OR = 1,
	T_AND,
	SEMICOLON,
	PIPE,
	AMPERSAND,
	REDIR_SUP,
	REDIR_INF,
	D_REDIR_INF,
	D_REDIR_SUP,
	AGGREGATOR = 10,
	IO_NUMBER,
	NEWLINE,
	DOLLAR,
	QUOTE,
	DQUOTE,
	WORD,
	STD_SEPARATOR,
	INIT,
}						t_token;

typedef struct			s_lexer_id
{
	struct s_lexer_id	*prev;
	char				data;
	t_token				type;
	struct s_lexer_id	*next;
}						t_lexer_id;

typedef struct			s_lexer
{
	struct s_lexer		*prev;
	char				*data;
	t_token				type;
	int					status;
	int8_t				status_line;
	char				*path_heredoc;
	bool				separator;
	struct s_lexer		*next;
}						t_lexer;

/*
**  ----------------------------------------------------------------------------
**							--	FUNCTIONS --
**  ----------------------------------------------------------------------------
*/

/*
**	--	lexer.c --
*/

char					*here_doc(void);
int						search_heredoc(t_lexer *lexer);

/*
**	--	lexer.c --
*/

t_lexer					*lexing(char *command);
void					tokenizer(t_lexer_id *lexer_id, t_lexer **lexer);
void					free_lexer(t_lexer **lexer);

/*
**	--	id_list.c --
*/

void					id_lexer_add_end(t_lexer **lexer, char *data,\
						t_token type);
t_lexer					*create_lexer_node(char *data, t_token type);
void					free_lexer_id(t_lexer_id **lexer_id);
void					lexer_add_end(t_lexer **lexer,
						char *data, t_token type);

/*
**	--	lexer_split.c --
*/

char					**lexer_split(char *s);

/*
**	--	lexer_id.c --
*/

void					ref_token(t_lexer_id **lexer, char *str);
t_lexer_id				*analyse(char *command);

/*
**	--	lexer_tools.c --
*/

bool					is_escape(char *str, size_t i);
void					add_token(t_lexer_id *id_ptr,
						t_lexer **lexer, size_t len);
void					print_lexer_list(t_lexer *lexer);

/*
**	--	lexer_id_list.c --
*/

void					print_lexer_idlist(t_lexer_id *lexer);
t_lexer_id				*create_lexer_id_node(char data, t_token type);
void					lexer_id_add_end(t_lexer_id **lexer,
						char data, t_token type);
t_lexer_id				*lexer_id_init(void);
char					*lexer_word_create(char *command,
						bool *quote, bool *dquote);

/*
**	--	syntax_parseur.c --
*/

int						syntax_parseur(t_lexer *lexer);

/*
**	--	lexer_d_quote.c --
*/

t_lexer					*lexer_d_quote(t_lexer *lexer);

/*
**	--	remove_command_part.c --
*/

t_lexer					*remove_useless_semicon(t_lexer *lexer);

#endif
