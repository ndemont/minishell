/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 23:33:16 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/17 23:33:36 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_semicolon(t_node **tokens, t_big *datas, int i)
{
	if (tokens[i]->right)
	{
		datas->root = tokens[i]->right;
		tokens[i]->right = 0;
		datas->root->left = tokens[i];
	}
	else
		datas->root = tokens[i];
}

void	next_semicolon(t_node **tokens, t_big *datas, int i)
{
	if (tokens[i]->right)
	{
		tokens[i]->left = datas->root;
		datas->root = tokens[i]->right;
		tokens[i]->right = 0;
		datas->root->left = tokens[i];
	}
	else
	{
		tokens[i]->left = datas->root;
		datas->root = tokens[i];
	}
}

void	semicolon_node(t_node **tokens, t_big *datas, int i)
{
	if (tokens && tokens[i] && i == 0)
		first_semicolon(tokens, datas, i);
	else if (tokens && tokens[i])
		next_semicolon(tokens, datas, i);
}
