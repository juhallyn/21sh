/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziyan <mmeziyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:46:15 by mmeziyan          #+#    #+#             */
/*   Updated: 2018/06/15 03:46:18 by mmeziyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ast		*new_root(t_lexer *lexer_node)
{
	t_ast	root;

	root = NULL;
	root = (t_ast*)malloc(sizeof(*root));
	if (!root)
		ft_fatalexit("allocation fail for `root` in new_head");
	root->type = 42;
	root->lexer_node = NULL;
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
}
