/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:58:24 by ndemont           #+#    #+#             */
/*   Updated: 2021/03/29 16:16:27 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_arg(char *input)
{
	char *arg;

	arg = 0;
	(void)input;
	return (arg);
}

void	get_buildin(t_node *token)
{
	char *list[8] = {"echo", "export", "env", "cd", "pwd", "unset", "exit", "$?"};
	int i;

	i = 0;
	(void)list;
	while (token->input[i])
	{
		i++;
	}
}

t_node	**ft_buldin_parser(t_node **token_tab)
{
	int i;

	i = 0;
	while (token_tab[i])
	{
		if (!token_tab[i]->type)
			get_buildin(token_tab[i]);
		i++;
	}
	return (token_tab);
}
