/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:33:27 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/25 22:05:24 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	browse_quote(int *i, char *input)
{
	*i = *i + 1;
	while (input[*i] && !(input[*i] == '"'))
	{
		if (input[*i] == '\\')
			while (input[*i] == '\\')
				*i = *i + 2;
		else
			*i = *i + 1;
	}
}

t_node	*ft_new_builtin_node(int *i, char *input)
{
	int		j;
	t_node	*new_node;

	new_node = 0;
	j = *i;
	while (input[*i] && gram(input, *i) <= 0)
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
			browse_quote(i, input);
		*i = *i + 1;
	}
	new_node = ft_init_buildin_node(ft_substr(input, j, (*i - j)), 0);
	return (new_node);
}

t_node	*ft_new_node(char *input, int *i)
{
	int		type;
	t_node	*new_node;

	new_node = 0;
	while (input[*i] && input[*i] == ' ' && input[*i] == '\t')
		*i = *i + 1;
	type = gram(input, *i);
	if ((type))
	{
		new_node = ft_init_grammar_node(type);
		if (!new_node)
			return (0);
		*i = *i + 1;
		if (type == 2)
			*i = *i + 1;
	}
	else
	{
		new_node = ft_new_builtin_node(i, input);
		if (!new_node)
			return (0);
	}
	return (new_node);
}

int	ft_check_node_error(t_node **nodes, int j)
{
	if (j == 0 && nodes[j]->type)
	{
		g_tcaps.ret = 2;
		return (printi_stderr(0, "syntax error", 1));
	}
	else if (j != 0 && nodes[j]->type && nodes[j - 1]->type)
	{
		g_tcaps.ret = 2;
		return (printi_stderr(0, "syntax error", 1));
	}
	return (1);
}

t_node	**ft_create_nodes(char *input, int nb)
{
	t_node	**node;
	int		j;
	int		i;

	node = (t_node **)malloc(sizeof(t_node) * (nb + 1));
	if (!(node))
		return (0);
	node[nb] = 0;
	j = 0;
	i = 0;
	while (j < nb)
	{
		node[j] = ft_new_node(input, &i);
		if (!node[j])
			return (0);
		if (!(ft_check_node_error(node, j++)))
			return (0);
	}
	return (node);
}
