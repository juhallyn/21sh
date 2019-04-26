/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 19:48:11 by mmeziyan          #+#    #+#             */
/*   Updated: 2017/12/25 19:48:12 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabcpy(char **tab)
{
	int		n;
	char	**new;

	n = ft_tabtool(tab, "len");
	if (!(new = malloc(sizeof(char *) * (n + 1))))
		exit(-1);
	n = -1;
	while (tab[++n])
		new[n] = ft_strdup(tab[n]);
	new[n] = NULL;
	return (new);
}
