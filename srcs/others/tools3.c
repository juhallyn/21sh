/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:50:19 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 20:12:47 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*random_str(int len)
{
	char	*str;
	int		n;
	char	chars[53];
	int		fd;

	ft_strcpy(chars, "abcdefghijklmnpqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01");
	n = 0;
	if ((fd = open("/dev/random", O_RDONLY)) == -1)
		return (NULL);
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	while (--len >= 0)
	{
		read(fd, &n, 1);
		n = (n < 0) ? -n % 52 : n % 52;
		str[len] = chars[n];
	}
	close(fd);
	return (str);
}

char		*create_tmp_file(void)
{
	char	*str;
	char	*path;
	int		fd;

	path = NULL;
	str = random_str(15);
	path = ft_strjoin("/tmp/.21sh_", str);
	ft_strdel(&str);
	if ((fd = open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
	{
		ft_strdel(&path);
		path = create_tmp_file();
	}
	close(fd);
	return (path);
}

void		i_exp(char **s1, char **s2, char **s3, char **s4)
{
	*s1 = NULL;
	*s2 = NULL;
	*s3 = NULL;
	*s4 = NULL;
}
