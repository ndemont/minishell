/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:13:52 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/07 14:02:21 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_node *root)
{
	if (root->left)
	{
		print_tree(root->left);
	}
	if (root->right)
	{
		print_tree(root->right);
	}
	if (root->type)
	{
		write(1, "grammar type ", 14);
		write(1, ft_itoa(root->type), 1);
		write(1, "\n", 1);
	}
	else
	{
		write(1, root->arg[0], ft_strlen(root->arg[0]));
		write(1, "\n", 1);
	}
}

void	tree(t_node **tokens, t_big *datas)
{
	int		i;
	int		j;
	int		count;
	t_node	**tmp;
	
	i = 0;
	count = 0;
	datas->root = tokens[0];
	while (tokens[i])
	{
		if (tokens[i]->type)
		{
			if (i > 0)
				tokens[i]->left = tokens[i - 1];
			if (tokens[i + 1])
				tokens[i]->right = tokens[i + 1];
			count++;
		}
		i++;
	}
	printf("count = %d\n", count);
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
	//free(tmp);
	i = 1;
	while (tokens[i])
	{
		if (tokens[i]->type)
		{
			if (tokens[i]->type == 5)
				tokens[i - 1]->right = tokens[i];
			else
			{
				tokens[i]->left = datas->root;
				datas->root = tokens[i];
			}
		}
		i++;
	}
	write(1, "\n", 1);
	print_tree(datas->root);
	write(1, "\n", 1);
}