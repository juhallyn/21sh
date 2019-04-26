/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 01:10:11 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/02/15 22:12:32 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *ntpr)
{
	int		i;
	long	n;
	int		neg;

	n = 0;
	i = 0;
	neg = 1;
	while (((ntpr[i] >= 9) && (ntpr[i] <= 13)) || (ntpr[i] == '+' \
				&& ft_isdigit(ntpr[i + 1])) || ntpr[i] == ' ')
		i++;
	if (ft_strcmp((char *)ntpr, "-2147483648") == 1)
		return (-2147483648);
	if (ntpr[i] == '-' && ft_isdigit(ntpr[i++ + 1]))
		neg = -1;
	while (ft_isdigit(ntpr[i]))
		n = (n * 10) + (ntpr[i++] - '0');
	return ((int)(n * neg));
}
