/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branches.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 23:04:07 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/30 20:15:15 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	semicolon_node(t_node **tokens, t_big *datas, int i)
{
	t_node	*tmp;

	if (i == 0)
	{
		datas->root = tokens[i]->right;
		tokens[i]->right = 0;
		datas->root->left = tokens[i];
	}
	else
	{
		tmp = datas->root;
		datas->root = tokens[i]->right;
		tokens[i]->left = tmp;
		tokens[i]->right = 0;
		datas->root->left = tokens[i];
	}
}

void	right_redirection_node(t_node **tokens, t_big *datas, int i, t_node *prev)
{
	t_node	*tmp;

	tmp = tokens[i]->right;
	tokens[i]->right = tokens[i]->left;
	tokens[i]->left = tmp;
	if (i == 0)
		datas->root = tokens[i];
	else if (prev->type != 3 && prev->type != 2)
		datas->root->right = tokens[i];
	else if (prev->type == 3 || prev->type == 2)
	{
		tmp = prev->left;
		while (tmp->right)
			tmp = tmp->right;
		tokens[i]->right = 0;
		tmp->right = tokens[i];
	}
}

void	left_redirection_node(t_node **tokens, t_big *datas, int i)
{
	t_node	*tmp;

	tmp = datas->root;
	if (i == 0)
	{
		datas->root = tokens[i];
		datas->root->right = datas->root->left;
		datas->root->left = tokens[i]->right;
	}
	else if (datas->root->type == 2 || datas->root->type == 3)
	{
		while (tmp->right)
			tmp = tmp->right;
		tokens[i]->left = tokens[i]->right;
		tokens[i]->right = 0;
		tmp->right = tokens[i];
	}
	else if (datas->root->type == 4)
	{
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = tokens[i];
		tmp->left->left = tokens[i]->right;
		tmp->left->right = 0;
	}
}

void	pipe_node(t_node **tokens, t_big *datas, int i)
{
	if (i == 0)
		datas->root = tokens[i];
	else
	{
		tokens[i]->left = datas->root;
		datas->root = tokens[i];
	}
}
