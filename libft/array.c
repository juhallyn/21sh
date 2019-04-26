/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 19:48:11 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/20 05:28:29 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	put_array(char **array)
{
	int	n;

	n = -1;
	while (array[++n])
		ft_putendl(array[n]);
}

int		array_len(char **array)
{
	int	n;

	n = -1;
	while (array[++n])
		;
	return (n);
}

void	array_free(char ***array)
{
	int	n;

	n = -1;
	while ((*array)[++n])
	{
		free((*array)[n]);
		(*array)[n] = NULL;
	}
	free(*array);
	*array = NULL;
}

void	free_tab(char ***tab)
{
	int	n;

	n = -1;
	while ((*tab)[++n])
	{
		free((*tab)[n]);
		(*tab)[n] = NULL;
	}
	free(*tab);
	*tab = NULL;
}

char	**array_dup(char **array)
{
	int		n;
	char	**new;

	if (!array || !*array)
		return (NULL);
	n = array_len(array);
	if (n < 1 || !(new = malloc(sizeof(char *) * (n + 1))))
		return (NULL);
	n = -1;
	while (array[++n])
		new[n] = ft_strdup(array[n]);
	new[n] = NULL;
	return (new);
}
