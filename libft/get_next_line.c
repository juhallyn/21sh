/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 20:06:21 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/08/14 20:06:23 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	read_from_fd_into_stock(int const fd, char **stock)
{
	static char	buff[BUFF_SIZE + 1] = { '\n' };
	int			read_bytes;
	char		*nstr;

	read_bytes = read(fd, buff, BUFF_SIZE);
	if (read_bytes > 0)
	{
		buff[read_bytes] = '\0';
		if (!(nstr = ft_strjoin(*stock, buff)))
			return (-1);
		free(*stock);
		*stock = nstr;
	}
	return (read_bytes);
}

int	get_next_line(int const fd, char **line)
{
	static char	*stock = NULL;
	char		*endl_index;
	int			ret;

	if (!stock && (stock = (char *)ft_memalloc(sizeof(char))) == NULL)
		return (-1);
	endl_index = ft_strchr(stock, '\n');
	while (endl_index == NULL)
	{
		if ((ret = read_from_fd_into_stock(fd, &stock)) == 0)
			if ((endl_index = ft_strchr(stock, '\0')) == stock)
				return (0);
		if (ret < 0)
			return (-1);
		if (ret > 0)
			endl_index = ft_strchr(stock, '\n');
	}
	if (!(*line = ft_strsub(stock, 0, endl_index - stock)))
		return (-1);
	endl_index = ft_strdup(endl_index + 1);
	free(stock);
	stock = endl_index;
	return (1);
}
