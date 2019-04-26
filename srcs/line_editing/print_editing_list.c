/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_editing_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:41:46 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/03/15 19:45:32 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	print_editing_list(t_line *edit_line)
{
	int i;

	i = 0;
	if (!edit_line)
		return (0);
	while (edit_line)
	{
		if (edit_line->c == NEWLINE_ANSI)
			ft_putchar('^');
		else if (edit_line->c == '\n')
			ft_putchar('J');
		else
			ft_putchar(edit_line->c);
		edit_line = edit_line->next;
		i++;
	}
	return (i);
}
