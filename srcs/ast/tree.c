/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:13:52 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/30 20:12:38 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_node *root)
{
	if (root->left)
		print_tree(root->left);
	if (root->right)
		print_tree(root->right);
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
	t_node	*prev;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i]->type)
			tokens[j++] = tmp[i];
		i++;
	}
	i = 0;
	prev = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == 5)
			semicolon_node(tokens, datas, i);
		else if (tokens[i]->type == 3 || tokens[i]->type == 2)
			right_redirection_node(tokens, datas, i, prev);
		else if (tokens[i]->type == 4)
			left_redirection_node(tokens, datas, i);
		else if (tokens[i]->type == 1)
			pipe_node(tokens, datas, i);
		prev = tokens[i];
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
