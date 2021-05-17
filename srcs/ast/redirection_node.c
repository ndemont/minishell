/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 23:13:04 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/17 23:26:32 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_children(t_node **tokens, int i)
{
	t_node	*tmp;

	tmp = tokens[i]->right;
	tokens[i]->right = tokens[i]->left;
	tokens[i]->left = tmp;
}

void	first_redirection(t_node **tokens, t_big *datas, int i)
{
	datas->root = tokens[i]->right;
	tokens[i]->right = 0;
	datas->root->left = tokens[i];
}

void	next_redirection(t_node **tokens, int i, t_node *prev)
{
	t_node	*tmp;

	tmp = prev;
	while (tmp->right)
		tmp = tmp->right;
	tokens[i]->right = 0;
	tmp->right = tokens[i];
}

void	right_redir_node(t_node **tokens, t_big *datas, int i, t_node *prev)
{
	swap_children(tokens, i);
	if (i == 0)
		first_redirection(tokens, datas, i);
	else if (prev->type >= 2 && prev->type <= 4)
		next_redirection(tokens, i, prev);
	else if (prev->type == 5)
	{
		tokens[i]->left->left = datas->root->left;
		datas->root = tokens[i]->right;
		tokens[i]->right = 0;
		datas->root->left = tokens[i];
	}
	else
	{
		datas->root->right = 0;
		tokens[i]->left->left = datas->root;
		datas->root = tokens[i]->right;
		tokens[i]->right = 0;
		datas->root->left = tokens[i];
	}
}

void	left_redir_node(t_node **tokens, t_big *datas, int i, t_node *prev)
{
	swap_children(tokens, i);
	if (i == 0)
		first_redirection(tokens, datas, i);
	else if (prev->type >= 2 && prev->type <= 4)
		next_redirection(tokens, i, prev);
	else if (prev->type == 5)
	{
		tokens[i]->left->left = datas->root->left;
		datas->root = tokens[i]->right;
		tokens[i]->right = 0;
		datas->root->left = tokens[i];
	}
	else
		datas->root->right = tokens[i];
}
