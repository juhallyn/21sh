/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:30:43 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/20 07:55:58 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include "shell.h"

# define PROMPT_SIZE		7
# define SIZE_CHANGED		2
# define HIST_SIZE			100000
# define CHAR_QUOTE			39
# define CHAR_DQUOTE		34
# define NEWLINE_ANSI		1247697690

/*
**	--	PROMPT MODE --
*/

# define PROMPT_STANDARD	1
# define PROMPT_HEREDOC		2
# define PROMPT_DQUOTE		3
# define PROMPT_QUOTE		4
# define PROMPT_ERR			5

/*
**	--	KEYS --
*/

# define HOME				4741915
# define END				4610843

# define UP_ARROW 			4283163
# define DOWN_ARROW 		4348699
# define LEFT_ARROW 		4479771
# define RIGHT_ARROW		4414235
# define ESC				27
# define SPACE				32
# define DEL				2117294875
# define BACKSPACE			127
# define ENTER				10
# define TAB				9

# define ALT_V				6715422
# define ALT_B				11241698
# define ALT_D				8554722
# define ALT_F				37574
# define ALT_C				22845
# define ALT_SUP			10848738
# define ALT_INF			10783202

# define ALT_LEFT			1146821403
# define ALT_RIGHT			1130044187

# define CTRL_F				6
# define CTRL_G				7
# define CTRL_H				8

# define CTRL_K				11
# define CTRL_U				21
# define CTRL_A				1
# define CTRL_E				5
# define CTRL_L				12
# define CTRL_D				4

/*
**	--	COLORS --
*/

# define RED   				"\x1B[31m"
# define GRN   				"\x1B[32m"
# define YEL   				"\x1B[33m"
# define BLU   				"\x1B[34m"
# define MAG   				"\x1B[35m"
# define CYN   				"\x1B[36m"
# define WHT   				"\x1B[37m"
# define RESET 				"\x1B[0m"

/*
**	--	TERMCAPS --
*/

# define DELETE_BEHIND		"cd"
# define VISUAL_CURSOR		"ve"
# define HIDDEN_CURSOR		"vi"
# define MOVE_LEFT			"le"
# define MOVE_RIGHT			"nd"
# define MOVE_DOWN			"do"
# define MOVE_UP			"up"
# define CLEAR				"cl"
# define SAVE_POS			"sc"
# define REST_POS			"rc"
# define INIT_POS			"cr"

/*
**  ----------------------------------------------------------------------------
**							--	STRUCTS --
**  ----------------------------------------------------------------------------
*/

/*
**	--			LINE			--
*/

typedef struct		s_line
{
	int					c;
	struct s_line		*next;
	struct s_line		*prev;
}					t_line;

typedef struct		s_line_stat
{
	size_t				win_index;
	size_t				cursor_index;
	size_t				history_index;
	size_t				focus_line;
	size_t				insert_line;
	size_t				nb_line;
	size_t				nb_char;
	int					prompt_mode;
	int					prompt_size;
	bool				visual_select;
}					t_line_stat;

/*
**	--			LINE_HISTORY 			--
**			(limited by HIST_SIZE)
*/

typedef struct		s_hist_data
{
	char				*data;
	struct s_hist_data	*next;
}					t_hist_data;

typedef struct		s_history
{
	int					history_fd;
	char				*current_line;
	bool				is_init;
	size_t				nb_hist_line;
	struct s_hist_data	*history_list;
	struct s_hist_data	*history_tab;
}					t_history;

/*
**  ----------------------------------------------------------------------------
**							--	FUNCTIONS --
**  ----------------------------------------------------------------------------
*/

/*
**	--	history_access.c --
*/

void				read_history_up(t_line **edit_line, t_line_stat *stat);
void				read_history_down(t_line **edit_line, t_line_stat *stat);

/*
**	--	history_list.c --
*/

void				add_end_history(t_hist_data **history_list, char *data);
t_hist_data			*reference_list(t_history *history);
t_hist_data			*fill_history_list(t_history *history);

/*
**	--	init_history.c --
*/

int					init_history_fd(void);
t_history			*init_history(void);
int					nb_line_history(int history_fd);

/*
**	--	line_history.c --
*/

int					add_to_history(char *command, t_line_stat *stat);

/*
**	--	check_d_quote.c --
*/

int					check_close_d_quote(t_line *edit_line);
int					to_close(t_line *edit_line);

/*
**	--	check_nl.c --
*/

bool				nl_backspace(t_line_stat *stat);

/*
**	--	d_quote.c --
*/

int					init_ret_quote(int mode, t_line **edit_line, \
					t_line **j_line);
int					line_d_quote(int ret_quote, t_line **edit_line, \
					t_line **j_line, t_line_stat **stat);

/*
**	--	eof_key.c --
*/

int					eof_key(t_line **edit_line, t_line_stat *stat);

/*
**	--	keys_actions.c --
*/

int					ft_edit_line(t_line **edit_line, t_line_stat *stat,\
					int key);

/*
**	--	keys_actions2.c --
*/

int					error_key(t_line **edit_line, t_line_stat *stat, int key);
int					newline_eof(t_line **edit_line, t_line_stat *stat, int key);

/*
**	--	line_init.c --
*/

void				print_prompt(int cmd_return, int prompt_mode, int size);
t_line_stat			*init_line_stat(void);
t_line				*malloc_line_nodie(void);
t_line				*init_line(int key);

/*
**	--	line_operations.c --
*/

void				insertion(t_line_stat *stat, t_line **edit_line, int key);
t_line				*delete(t_line **edit_line, size_t cursor_index);
void				backspace_delete(t_line_stat *stat, t_line **edit_line);
void				delete_line(t_line **edit_line, t_line_stat *stat);
void				del_delete(t_line_stat *stat, t_line **edit_line);

/*
**	--	line_paste.c --
*/

int					paste_mod(char *str_key, t_line **edit_line, \
					t_line_stat *stat);

/*
**	--	line_refresh.c --
*/

void				refresh_del(t_line *tmp, bool up, t_line_stat *stat);
void				refresh_add(t_line *tmp);
void				refresh_line(t_line_stat *stat);

/*
**	--	line_shortcuts.c --
*/

void				go_to_next_word(t_line **edit_line, t_line_stat *stat);
void				go_to_back_word(t_line **edit_line, t_line_stat *stat);

/*
**	--	line_tools2.c --
*/

char				*list_to_str(t_line **edit_line, bool free);
void				read_err_free(t_line_stat **stat);
void				reset_stat(t_line_stat **stat, int prompt_mode);

/*
**	--	line_tools.c --
*/

t_line				*move_list_to_cursor(t_line **edit_line, \
					size_t cursor_index);
size_t				list_len(t_line *edit_line);
void				free_list(t_line **edit_line, bool std);
char				*remove_newline_ansi(char *command);
char				*malloc_str(t_line *edit_line);

/*
**	--	list_adding.c --
*/

void				add_char(t_line **edit_line, int key,\
					t_line_stat *stat);
void				add_end(t_line **edit_line, int key);

/*
**	--	list_deleting.c --
*/

void				delete_char(t_line **to_del);

/*
**	--	move_cursor.c --
*/

void				move_left(t_line_stat *stat);
void				move_right(t_line_stat *stat);

/*
**	--	move_cursor2.c --
*/

void				move_begin(t_line *edit_line, t_line_stat *stat);
void				move_end(t_line *edit_line, t_line_stat *stat);

/*
**	--	print_editing_list.c --
*/

int					print_editing_list(t_line *edit_line);

/*
**	--	prompt_mode.c --
*/

void				join_line(char *command, t_line **j_line);
int					write_prompt(int prompt_mode);
int					prompt_mode(t_line_stat **stat, t_line **edit_line);
void				init_prompt_size(t_line_stat *stat);

/*
**	--	readline.c --
*/

char				*readline(t_line **edit_line);
char				*line_editing(int cmd_return);

/*
**	--	refresh_stat.c --
*/

void				increment_stat(t_line_stat **stat);
void				decrement_stat(t_line_stat **stat);

/*
**	--	replace_cursor.c --
*/

void				replace_cursor(t_line_stat *stat, t_line *edit_line);
void				check_insert_line(t_line **edit_line, t_line_stat *stat);
void				check_del_line(t_line_stat *stat);

/*
**	--	replace_cursor.c --
*/

int					visual_mode(t_line **edit_line, t_line_stat *stat);

#endif
