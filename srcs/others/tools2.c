/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:50:19 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/19 20:12:47 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char				*ft_justnum(char *str)
{
	int		n;

	n = -1;
	while (str[++n])
	{
		if (!ft_isdigit(str[n]))
			return (str + n);
	}
	return (NULL);
}

int					ft_ischar(int key)
{
	if ((key <= 126 && key >= 32) || key == 10)
		return (1);
	return (0);
}

int					is_nb(char *nbr)
{
	if (!nbr)
		return (-1);
	while (*nbr)
	{
		if ((*nbr < '0' && *nbr > '9') || *nbr != '-')
			return (-1);
		nbr++;
	}
	return (0);
}

size_t				ft_power(int n, int p)
{
	size_t	result;

	result = 1;
	if (p < 0)
		return (-1);
	if (p == 0)
		return (1);
	while (p > 0)
	{
		result *= n;
		p--;
	}
	return (result);
}

int					ft_atoi_mod(char *str)
{
	long int	nbr;
	int			n;
	int			multi;

	nbr = 0;
	multi = 0;
	n = -1;
	while (str[++n] && n < 8)
	{
		if (str[n])
			nbr += str[n] * ft_power(2, multi);
		multi += 8;
	}
	nbr = (nbr < 0) ? -nbr : nbr;
	return (nbr);
}
