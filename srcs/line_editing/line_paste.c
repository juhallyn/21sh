/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 20:35:30 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/04/22 02:42:44 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static inline void	paste_routine(char *str_key, t_line **edit_line, \
					t_line_stat *stat)
{
	size_t	i;

	i = 0;
	while (str_key[i])
	{
		if (ft_ischar(str_key[i]))
		{
			if (str_key[i] == '\n')
			{
				insertion(stat, edit_line, NEWLINE_ANSI);
				insertion(stat, edit_line, '\n');
			}
			else
				ft_edit_line(edit_line, stat, str_key[i]);
		}
		i++;
	}
}

int					paste_mod(char *str_key, t_line **edit_line,\
					t_line_stat *stat)
{
	if (!str_key)
		return (1);
	if (ft_strlen(str_key) > 1 && ft_ischar(str_key[0])
	&& ft_atoi_mod(str_key) != ENTER)
		paste_routine(str_key, edit_line, stat);
	return (0);
}
