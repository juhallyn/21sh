/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 18:30:57 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/02/21 19:37:32 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_intlen(long int n)
{
	int i;
	int neg;

	neg = 0;
	i = 1;
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i + neg);
}

static	int	ft_positive(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char		*ft_itoa(int n)
{
	char	*nb;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = ft_intlen(n);
	if (!(nb = ft_strnew(i)))
		return (NULL);
	nb[i] = '\0';
	nb[0] = '-';
	while (i)
	{
		nb[--i] = ((ft_positive(n) % 10) + 48);
		if ((n < 0) && ((n / 10) == 0))
			return (nb);
		n /= 10;
	}
	return (nb);
}
