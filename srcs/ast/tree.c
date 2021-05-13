/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 15:13:52 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/11 11:24:26 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_count_nodes(t_node **tokens, t_big *datas)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
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
	int				i;
	int				j;
	static t_node	*prev = 0;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i]->type)
			tokens[j++] = tmp[i];
		i++;
	}
	i = 0;
	tokens[j] = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == 5)
			semicolon_node(tokens, datas, i);
		else if (tokens[i]->type == 3 || tokens[i]->type == 2)
			right_redirection_node(tokens, datas, i, prev);
		else if (tokens[i]->type == 4)
			left_redirection_node(tokens, datas, i, prev);
		else if (tokens[i]->type == 1)
			pipe_node(tokens, datas, i);
		prev = tokens[i];
		i++;
	}
}

int		tree(t_node **tokens, t_big *datas)
{
	int		count;
	t_node	**tmp;

	datas->root = tokens[0];
	count = 0;
	count = ft_count_nodes(tokens, datas);
	tmp = tokens;
	tokens = malloc(sizeof(t_node *) * (count + 1));
	if (!tokens)
		return (0);
	tokens[count] = 0;
	if (count)
		create_tree(tokens, datas, tmp);
	if (tmp)
		free(tmp);
	free(tokens);
	return (1);
}