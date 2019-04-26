/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 10:31:40 by hp                #+#    #+#             */
/*   Updated: 2018/06/19 12:40:11 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			to_no_canonial(struct termios *term)
{
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_lflag |= ISIG;
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
}

static int			term_error(struct termios **term_canon)
{
	free(*term_canon);
	*term_canon = NULL;
	return (-1);
}

static int			check_term(struct termios **term_canon, bool b_canon)
{
	tcsetattr(0, TCSANOW, *term_canon);
	free(*term_canon);
	*term_canon = NULL;
	if (b_canon == true)
		return (0);
	return (1);
}

static int			check_term_name(void)
{
	char	*term_type;

	while (42)
	{
		if ((term_type = env_search("TERM") ? env_search("TERM")->value : NULL)
		&& tgetent(NULL, term_type) == 1)
			break ;
		my_printf("Press enter to default \"%sxterm%s\"", 2, MAG, RESET);
		my_printf("\n	Or set a TERM variable -> ", 2);
		get_next_line(0, &term_type);
		if (term_type && ft_strcmp(term_type, "") == 0)
			add_env("TERM", "xterm");
		else if (!term_type)
		{
			env_list_destroy();
			free(std_singleton(NULL));
			ft_putendl_fd("", 2);
			exit(0);
		}
		else if (tgetent(NULL, term_type) == 1)
			add_env("TERM", term_type);
		ft_strdel(&term_type);
	}
	return (0);
}

int					init_term_canon(bool b_canon)
{
	static struct termios	*term_canon = NULL;
	struct termios			term_no_canon;

	if (std_singleton(NULL)->stdin == true)
		return (-1);
	if (term_canon && (check_term(&term_canon, b_canon) == 0))
		return (0);
	check_term_name();
	if (tcgetattr(0, &term_no_canon) == -1)
		return (-1);
	if (!(term_canon = (struct termios *)malloc(sizeof(struct termios))))
	{
		term_canon = NULL;
		return (term_error(&term_canon));
	}
	if (!(ft_memcpy(term_canon, &term_no_canon, sizeof(struct termios))))
		return (term_error(&term_canon));
	to_no_canonial(&term_no_canon);
	if (tcsetattr(0, TCSANOW, &term_no_canon) == -1)
		return (term_error(&term_canon));
	return (0);
}
