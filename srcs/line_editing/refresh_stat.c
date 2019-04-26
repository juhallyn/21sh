/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_stat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 20:51:41 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/02/16 16:09:05 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		increment_stat(t_line_stat **stat)
{
	(*stat)->cursor_index++;
	(*stat)->nb_char++;
	(*stat)->win_index = (*stat)->prompt_size + (*stat)->cursor_index;
}

void		decrement_stat(t_line_stat **stat)
{
	(*stat)->cursor_index--;
	(*stat)->nb_char--;
	(*stat)->win_index = (*stat)->prompt_size + (*stat)->cursor_index;
}
