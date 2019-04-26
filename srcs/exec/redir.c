/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:33:38 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 02:16:50 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static	int		d_redir_sup(char *file, int fd_out, int info)
{
	char	c;

	c = 1;
	if ((fd_out = open(file, O_RDWR)) == -1)
		fd_out = open(file, O_RDWR | O_CREAT, \
		S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH);
	else if (fd_out == -1)
		my_printf("21sh: can't create %s\n", 2, file);
	if (info == 1)
		while (fd_out > 0 && read(fd_out, &c, 1) > 0)
			;
	return (fd_out);
}

int				ft_creat_file(char *file, t_token type, int info)
{
	int		fd_out;

	fd_out = 0;
	if (type == REDIR_INF && (fd_out = open(file, O_RDONLY)) == -1)
		my_printf("21sh: can't open %s: No such file or directory\n", 2, file);
	else if (fd_out == -1)
		my_printf("21sh: can't create %s: permission denied\n", 2, file);
	if (type == REDIR_SUP)
	{
		fd_out = open(file, O_WRONLY | O_TRUNC | O_CREAT, \
		S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR | S_IROTH);
		if (fd_out == -1)
			my_printf("21sh: can't create / open %s\n", 2, file);
	}
	if (type == D_REDIR_SUP)
		fd_out = d_redir_sup(file, fd_out, info);
	if (!fd_out && std_singleton(NULL)->stdin)
		exit(-1);
	return (fd_out);
}
