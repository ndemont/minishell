/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 13:06:25 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/06 16:03:45 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_isspace(char *input)
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

t_node		**ft_lexer(char *input)
{
	int		token_nb;
	t_node	**nodes_tab;

	token_nb = ft_count_tokens(input);
	if (token_nb < 0)
	{
		printf("minishellrose: missing char at end of line\n");
		return (0);
	}
	if (!token_nb)
		return (0);
	if (!check_isspace(input))
		return (0);
	nodes_tab = ft_create_nodes(input, token_nb);
	if (!nodes_tab)
		return (0);
	if (input)
	{
		free(input);
		input = 0;
	}
	return (nodes_tab);
}
