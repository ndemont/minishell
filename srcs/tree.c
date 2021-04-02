/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:13:52 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/02 16:42:02 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tree(t_node **tokens, t_big *datas)
{
	int		i;
	int		j;
	int		count;
	t_node	**root;
	t_node	**tmp;
	
	i = 1;
	count = 0;
	root = tokens[i];
	while (tokens[i])
	{
		if (tokens[i]->type)
		{
			tokens[i]->left = tokens[i - 1];
			tokens[i]->right = tokens[i + 1];
			count++;
		}
		i++;
	}
	tmp = tokens;
	tokens = malloc(sizeof(t_node *) * (count + 1));
	tokens[count] = 0;
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i]->type)
		{
			tokens[j] = tmp[i];
			j++;
		}
		i++;
	}
	free(tmp);
	root = tokens[0];
	i = 1;
	while (tokens[i])
	{
		if (tokens[i]->type)
		{
			if (tokens[i]->type == 5)
				tokens[i - 1]->right = tokens[i];
			else
			{
				tokens[i]->left = *root;
				root = &tokens[i];
			}
		}
		i++;
	}
}