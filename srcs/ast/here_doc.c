/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:45:13 by mmeziyan          #+#    #+#             */
/*   Updated: 2019/04/12 20:49:07 by juhallyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_tmp_urandom(void)
{
	int n;

	n = 0;
	if (access("/tmp", X_OK) == -1)
	{
		ft_puterror("/tmp is not accessible");
		n = -1;
	}
	else if (access("/dev/urandom", W_OK) == -1)
	{
		ft_puterror("/dev/urandom is not accessible");
		n = -1;
	}
	if (n == -1)
	{
		my_printf("%s/!\\\t\t21sh cannot use Heredoc\n%s", 2, RED, RESET);
		free_lexer(&std_singleton(NULL)->lexer);
	}
	return (n);
}

char		*stdin_here_doc(void)
{
	t_std	*std;
	char	*path;
	int		fd;
	char	*file;

	std = std_singleton(NULL);
	if (!(path = create_tmp_file()))
		exit(-1);
	if ((fd = open(path, O_WRONLY)) == -1)
		exit(-1);
	while ((get_next_line(0, &(std->heredoc_line)) > 0)
	&& ft_strcmp(std->heredoc_line, std->eof_str) != 0)
	{
		file = remove_newline_ansi(std->heredoc_line);
		ft_putendl_fd(file, fd);
		ft_strdel(&file);
	}
	close(fd);
	return (path);
}

int			search_heredoc(t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->type == D_REDIR_INF)
		{
			if (check_tmp_urandom() == -1)
				return (-1);
			if (lexer->next && lexer->next->type == STD_SEPARATOR)
				lexer = lexer->next;
			if (lexer->next && lexer->next->type == WORD)
				std_singleton(NULL)->eof_str = lexer->next->data;
			if (!lexer->next)
				return (-1);
			if (lexer->type != D_REDIR_INF)
				lexer = lexer->prev;
			lexer->path_heredoc = !std_singleton(NULL)->stdin ?
			here_doc() : stdin_here_doc();
			std_singleton(NULL)->eof_str = NULL;
		}
		lexer = lexer->next;
	}
	return (0);
}

char		*here_doc(void)
{
	t_std	*std;
	char	*path;
	int		fd;
	char	*file;

	std = std_singleton(NULL);
	if (!(path = create_tmp_file()))
		exit(-1);
	((fd = open(path, O_WRONLY)) == -1) ? exit(-1) : NULL;
	std->heredoc_list = init_line('\0');
	std->line = init_line('\0');
	std->stat = init_line_stat();
	reset_stat(&std->stat, PROMPT_HEREDOC);
	write_prompt(PROMPT_HEREDOC);
	if (readline(&std->line) && std->heredoc_line)
	{
		file = remove_newline_ansi(std->heredoc_line);
		std->heredoc_line = NULL;
		ft_putstr_fd(file, fd);
		ft_strdel(&file);
	}
	else
		ft_strdel(&std->heredoc_line);
	close(fd);
	return (path);
}
