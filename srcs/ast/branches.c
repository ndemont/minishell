/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branches.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 23:04:07 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/04 18:30:06 by ndemont          ###   ########.fr       */
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
	{
		datas->root = tokens[i]->right;
		tokens[i]->right = 0;
		datas->root->left = tokens[i];
	}
	else if (prev->type >= 2 && prev->type <= 4)
	{
		tmp = prev;
		while (tmp->right)
			tmp = tmp->right;
		tokens[i]->right = 0;
		tmp->right = tokens[i];
	}
	else
		datas->root->right = tokens[i];
}

void	left_redirection_node(t_node **tokens, t_big *datas, int i, t_node *prev)
{
	t_node	*tmp;

	tmp = tokens[i]->right;
	tokens[i]->right = tokens[i]->left;
	tokens[i]->left = tmp;
	if (i == 0)
	{
		datas->root = tokens[i]->right;
		tokens[i]->right = 0;
		datas->root->left = tokens[i];
	}
	else if (prev->type >= 2 && prev->type <= 4)
	{
		tmp = prev;
		while (tmp->right)
			tmp = tmp->right;
		tokens[i]->right = 0;
		tmp->right = tokens[i];
	}
	else
		datas->root->right = tokens[i];
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
