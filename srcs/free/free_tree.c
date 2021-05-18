/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:36:43 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/18 19:51:42 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arg(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		arg[i] = 0;
		i++;
	}
}

void	free_tree(t_node *root)
{
	if (root->left)
		free_tree(root->left);
	if (root->right)
		free_tree(root->right);
	if (root->input)
		clean_free(&root->input);
	if (root->arg)
	{
		free_arg(root->arg);
		free(root->arg);
		root->arg = 0;
	}
	if (root->builtin)
		clean_free(&root->builtin);
	if (root->command)
		clean_free(&root->command);
	if (root)
	{
		free(root);
		root = 0;
	}
}
