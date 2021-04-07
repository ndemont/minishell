/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 13:06:25 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/07 12:01:48 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_grammar(char *str, int i)
{
	if (str[i] == '|')
		return (1);
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (2);
		else
			return (3);
	}
	else if (str[i] == '<')
		return (4);
	else if (str[i] == ';')
		return (5);
	else
		return (0);
}

int		ft_is_quote(char *input, int i)
{
	int j;

	j = i;
	if (input[i] == '\'')
	{
		j++;
		while (input[j] && input[j] != '\'')
			j++;
		if (input[j] == '\'')
			return (j + 1);
		else
			return (-1);
	}
	else if (input[i] == '"')
	{
		j++;
		while (input[j] && input[j] != '"')
			j++;
		if (input[j] == '"')
			return (j + 1);
		else
			return (-1);
	}
	return (0);
}

int		ft_count_tokens(char *input)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] && !ft_is_grammar(input, i) && !ft_is_quote(input, i))
			i++;
		if (ft_is_grammar(input, i))
		{
			if (ft_is_grammar(input, i) == 2)
				i++;
			i++;
			j++;
		}
		else if (ft_is_quote(input, i))
			i = ft_is_quote(input, i);
		else
			break ;
	}
	return ((j * 2) + 1);
}

t_node	*ft_new_grammar_node(char *input, int i, int type)
{
	t_node *new;

	(void)input;
	(void)i;
	new = (t_node *)malloc(sizeof(t_node));
	new->type = type;
	new->input = 0;
	new->arg = 0;
	new->ret = 0;
	new->builtin = 0;
	new->command = 0;
	return (new);
}

t_node	*ft_new_buildin_node(char *input, int i, int type)
{
	t_node *new;

	(void)i;
	(void)type;
	new = (t_node *)malloc(sizeof(t_node));
	new->type = type;
	new->input = input;
	new->arg = 0;
	new->ret = 0;
	new->builtin = 0;
	return (new);
}

t_node	*ft_new_node(char *input, int *i)
{
	int		j;
	int		type;
	t_node	*new_node;

	new_node = 0;
	while (input[*i] && input[*i] == ' ')
		*i = *i + 1;
	if ((type = ft_is_grammar(input, *i)))
	{
		new_node = ft_new_grammar_node(input, *i, type);
		*i = *i + 1;
		if (type == 2)
			*i = *i + 1;
	}
	else
	{
		j = *i;
		while (input[*i] && ft_is_grammar(input, *i) <= 0)
		{
			if (input[*i] == '\'' || input[*i] == '"')
			{
				*i = *i + 1;
				while (input[*i] && input[*i] != '\'' && input[*i] != '"')
					*i = *i + 1;
			}
			*i = *i + 1;
		}
		new_node = ft_new_buildin_node(ft_substr(input, j, (*i - j)), *i, 0);
	}
	return (new_node);
}

t_node	**ft_create_nodes(char *input, int nb)
{
	t_node	**nodes;
	int		i;
	int		j;

	nodes = (t_node **)malloc(sizeof(t_node) * (nb + 1));
	nodes[nb] = 0;
	i = 0;
	j = 0;
	while (j < nb)
	{
		nodes[j] = ft_new_node(input, &i);
		j++;
	}
	return (nodes);
}

t_node	**ft_lexer(char *input)
{
	int		token_nb;
	t_node	**nodes_tab;

	token_nb = ft_count_tokens(input);
	nodes_tab = ft_create_nodes(input, token_nb);
	free(input);
	return (nodes_tab);
}
