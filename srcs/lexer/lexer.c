/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 13:06:25 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/07 18:25:40 by ndemont          ###   ########.fr       */
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
		if (ft_is_grammar(input, i) > 0)
		{

			if (ft_is_grammar(input, i) == 2)
				i++;
			i++;
			j++;
		}
		else if (ft_is_grammar(input, i) < 0)
			return (-1);
		else if (ft_is_quote(input, i) > 0)
			i = ft_is_quote(input, i);
		else if (ft_is_quote(input, i) < 0)
			return (-1);
		else
			break ;
	}
	if (!i)
		return (0);
	return ((j * 2) + 1);
}

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
			if (input[*i] == '\'' || input[*i] == '"')
			{
				*i = *i + 1;
				while (input[*i] && input[*i] != '\'' && input[*i] != '"')
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
	while (j < nb)
	{
		nodes[j] = ft_new_node(input, &i);
		if (j == 0 && nodes[j]->type)
			return (print_errors("minishellrose: syntax error near unexpected token"));
		else if (j != 0 && nodes[j]->type && nodes[j - 1]->type)
			return (print_errors("minishellrose: syntax error near unexpected token"));
		if (!nodes[j])
			return (0);
		j++;
	}
	if (!nodes[j - 1]->type && !nodes[j - 1]->input[0])
		return (print_errors("minishellrose: missing command at end of line"));
	return (nodes);
}

int  	check_isspace(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

t_node	**ft_lexer(char *input)
{
	int		token_nb;
	t_node	**nodes_tab;

	token_nb = ft_count_tokens(input);
	if (token_nb < 0)
		return (print_errors("minishellrose: missing quote at end of line"));
	if (!token_nb)
		return (0);
	if (!check_isspace(input))
		return (0);
	nodes_tab = ft_create_nodes(input, token_nb);
	if (!nodes_tab)
		return (0);
	if (input)
		free(input);
	return (nodes_tab);
}
