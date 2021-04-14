/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:33:27 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/14 16:47:07 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_new_grammar_node(int type)
{
	t_node *new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (0);
	new->type = type;
	new->input = 0;
	new->arg = 0;
	new->ret = 0;
	new->builtin = 0;
	new->command = 0;
	new->left = 0;
	new->right = 0;
	return (new);
}

t_node	*ft_new_buildin_node(char *input, int type)
{
	t_node *new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (0);
	new->type = type;
	if (!input)
		return (0);
	new->input = input;
	new->arg = 0;
	new->ret = 0;
	new->builtin = 0;
	new->left = 0;
	new->right = 0;
	return (new);
}

t_node	*ft_new_node(char *input, int *i)
{
	int		j;
	int		type;
	t_node	*new_node;

	new_node = 0;
	printf("input initial [%i] = [%c]\n", *i, input[*i]);
	while (input[*i] && input[*i] == ' ' && input[*i] == '\t')
		*i = *i + 1;
	if ((type = ft_is_grammar(input, *i)))
	{
		new_node = ft_new_grammar_node(type);
		if (!new_node)
			print_errors(strerror(errno));
		*i = *i + 1;
		if (type == 2)
			*i = *i + 1;
	}
	else
	{
		j = *i;
		while (input[*i] && ft_is_grammar(input, *i) <= 0)
		{
			if (input[*i] == '\\' && input[*i + 1])
				*i = *i + 1;
			else if (input[*i] == '\'')
			{
				*i = *i + 1;
				while (input[*i] && input[*i] != '\'')
					*i = *i + 1;
			}
			else if (input[*i] == '"')
			{
				*i = *i + 1;
				while (input[*i] && input[*i] != '"')
					*i = *i + 1;
			}
			*i = *i + 1;
		}
		new_node = ft_new_buildin_node(ft_substr(input, j, (*i - j)), 0);
		if (!new_node)
			print_errors(strerror(errno));
	}
	return (new_node);
}

t_node	**ft_create_nodes(char *input, int nb)
{
	t_node	**nodes;
	int		i;
	int		j;

	nodes = (t_node **)malloc(sizeof(t_node) * (nb + 1));
	if (!nodes)
		return (0);
	nodes[nb] = 0;
	i = 0;
	j = 0;
	printf("tokens = %d\n", nb);
	while (j < nb)
	{
		printf("token nb = %d\n", j);
		nodes[j] = ft_new_node(input, &i);
		if (j == 0 && nodes[j]->type)
			return (print_errors("minishellrose: syntax error"));
		else if (j != 0 && nodes[j]->type && nodes[j - 1]->type)
			return (print_errors("minishellrose: syntax error"));
		if (!nodes[j])
			return (0);
		j++;
	}
	if (!nodes[j - 1]->type && !nodes[j - 1]->input[0] && nodes[j - 2]->type < 5)
		return (print_errors("minishellrose: missing command at end of line"));
	return (nodes);
}
