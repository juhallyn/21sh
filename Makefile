# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/02 12:01:32 by mmeziyan          #+#    #+#              #
#    Updated: 2019/04/13 15:59:35 by juhallyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = 21sh

FLAGS += -Wall -Wextra -I Includes

SANITIZE += -g3 -fsanitize=address

OBJ = $(SRC:.c=.o)

SRC =	srcs/exec/exec.c\
		srcs/exec/redir.c\
		srcs/exec/fork_exec.c\
		\
		srcs/init/init_std.c\
		srcs/init/main.c\
		srcs/init/signal.c\
		srcs/init/term.c\
		\
		srcs/builtins_env/env.c\
		srcs/builtins_env/builtins.c\
		srcs/builtins_env/cd.c\
		srcs/builtins_env/env_tools.c\
		srcs/builtins_env/buil_env.c\
		srcs/builtins_env/init_env.c\
		\
		srcs/expansion/expand.c\
		\
		srcs/lexer/lexer.c\
		srcs/lexer/list.c\
		srcs/lexer/syntax_parseur.c\
		srcs/lexer/lexer_id.c\
		srcs/lexer/lexer_tools.c\
		srcs/lexer/id_list.c\
		srcs/lexer/lexer_split.c\
		srcs/lexer/lexer_d_quote.c\
		srcs/lexer/remove_command_part.c\
		\
		srcs/ast/ast.c\
		srcs/ast/separator.c\
		srcs/ast/separator_pipe.c\
		srcs/ast/ast_tools.c\
		srcs/ast/priority.c\
		srcs/ast/redir_tools.c\
		srcs/ast/redir.c\
		srcs/ast/do_redir.c\
		srcs/ast/here_doc.c\
		\
		srcs/line_editing/check_d_quote.c\
		srcs/line_editing/check_nl.c\
		srcs/line_editing/d_quote.c\
		srcs/line_editing/eof_key.c\
		srcs/line_editing/keys_actions.c\
		srcs/line_editing/keys_actions2.c\
		srcs/line_editing/history/history_access.c\
		srcs/line_editing/history/history_list.c\
		srcs/line_editing/history/init_history.c\
		srcs/line_editing/history/line_history.c\
		srcs/line_editing/line_init.c\
		srcs/line_editing/line_operations.c\
		srcs/line_editing/line_paste.c\
		srcs/line_editing/line_refresh.c\
		srcs/line_editing/line_shortcuts.c\
		srcs/line_editing/line_tools.c\
		srcs/line_editing/line_tools_2.c\
		srcs/line_editing/list_adding.c\
		srcs/line_editing/list_deleting.c\
		srcs/line_editing/move_cursor.c\
		srcs/line_editing/move_cursor2.c\
		srcs/line_editing/print_editing_list.c\
		srcs/line_editing/prompt_mode.c\
		srcs/line_editing/readline.c\
		srcs/line_editing/refresh_stat.c\
		srcs/line_editing/replace_cursor.c\
		\
		srcs/others/tools.c\
		srcs/others/tools2.c\
		srcs/others/tools3.c\
		\


LIBFT = libft/libft.a

LIBLOG = logger/liblogger.a

.PHONY = all clean fclean clean re

all: $(NAME)

$(OBJ): %.o: %.c
	gcc -c -I libft -I logger $(FLAGS) $< -o $@

$(LIBFT):
	make -C libft

$(NAME): $(LIBFT) $(OBJ)
	gcc $(OBJ) $(FLAGS) -I libft $(LIBFT) -lncurses -o $(NAME)

fs: $(LIBFT) $(OBJ)
	gcc $(OBJ) $(FLAGS) -I libft $(SANITIZE) $(LIBFT) -lncurses -o $(NAME)

clean:
	rm -rf $(OBJ)
	make -C libft clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

re: fclean
	make
