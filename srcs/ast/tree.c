/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:13:52 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/28 12:48:08 by ndemont          ###   ########.fr       */
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
		if (root->type == 1)
			write(1, "|", 1);
		if (root->type == 2)
			write(1, ">>", 2);
		if (root->type == 3)
			write(1, ">", 1);
		if (root->type == 4)
			write(1, "<", 1);
		if (root->type == 5)
			write(1, ";", 1);
		write(1, "\n", 1);
	}
	else
	{
		if (root->arg[0])
			write(1, root->arg[0], ft_strlen(root->arg[0]));
		write(1, "\n", 1);
	}
}

int		ft_count_nodes(t_node **tokens, t_big *datas)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	printf("count = %d\n", count);
	while (tokens[i])
	{
		if (tokens[i]->type)
		{
			if (!count)
				datas->root = tokens[i];
			if (i > 0)
				tokens[i]->left = tokens[i - 1];
			if (tokens[i + 1])
				tokens[i]->right = tokens[i + 1];
			count++;
		}
		i++;
	}
	return (count);
}

void	create_tree(t_node **tokens, t_big *datas, t_node **tmp)
{
	int		i;
	int		j;
	t_node	*test;

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
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == 5)
		{
			if (i == 0)
			{
				datas->root = tokens[i]->right;
				tokens[i]->right = 0;
				datas->root->left = tokens[i];
			}
			else
			{
				test = datas->root;
				datas->root = tokens[i]->right;
				tokens[i]->left = test;
				tokens[i]->right = 0;
				datas->root->left =  tokens[i];
			}
		}
		else if (tokens[i]->type == 3 || tokens[i]->type == 2)
		{
			if (i == 0)
				datas->root = tokens[i];
			else if (datas->root->type != 3 && datas->root->type != 2)
			{
				tokens[i]->left = datas->root;
				datas->root = tokens[i];
			}
			else if (datas->root->type == 3 || datas->root->type == 2)
			{
				test = datas->root;
				while (test->right)
					test = test->right;
				tokens[i]->left = 0;
				test->right = tokens[i];
			}
		}
		else if (tokens[i]->type == 4)
		{
			if (i == 0)
			{
				datas->root = tokens[i];
				test = tokens[i]->right;
				datas->root->right = datas->root->left;
				datas->root->left = test;
			}
			else if (datas->root->type == 2 || datas->root->type == 3)
			{
				test = datas->root;
				while (test->right)
					test = test->right;
				tokens[i]->left = tokens[i]->right;
				tokens[i]->right = 0;
				test->right = tokens[i];
			}
			else if (datas->root->type == 4)
			{
				test = datas->root;
				while (test->left)
					test = test->left;
				test->left = tokens[i];
				test->left->left = tokens[i]->right;
				test->left->right = 0;
			}
		}
		else if (tokens[i]->type == 1)
		{
			if (i == 0)
				datas->root = tokens[i];
			else
			{
				tokens[i]->left = datas->root;
				datas->root = tokens[i];
			}
		}
		i++;
	}
}

void	tree(t_node **tokens, t_big *datas)
{
	int		count;
	t_node	**tmp;

	datas->root = tokens[0];
	count = 0;
	count = ft_count_nodes(tokens, datas);
	tmp = tokens;
	tokens = malloc(sizeof(t_node *) * (count + 1));
	if (!tokens)
		print_errors(strerror(errno));
	tokens[count] = 0;
	if (count)
		create_tree(tokens, datas, tmp);
	printf("TREE");
	printf("\n-----\n");
	print_tree(datas->root);
	printf("\n");
}
