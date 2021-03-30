/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:58:24 by ndemont           #+#    #+#             */
/*   Updated: 2021/03/30 12:34:43 by ndemont          ###   ########.fr       */
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

int	count_arg(char *input)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (input[i])
	{
		count++;
		while (input[i] && input[i] == ' ')
			i++;
		while (input[i] && input[i] != ' ' && input[i] != '\'' && input[i] != '"')
			i++;
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'')
				i++;
		}
		else if (input[i] == '"')
		{
			i++;
			while (input[i] != '"')
				i++;
		}
		else if (!input[i])
			break ;
		i++;
	}
	return (count);
}

void	get_buildin(t_node *token)
{
	char *list[8] = {"echo", "export", "env", "cd", "pwd", "unset", "exit", "$?"};
	int i;
	int count;

	(void)list;
	i = 0;
	printf("token input = [%s]\n", token->input);
	count = count_arg(token->input);
	printf("count = %i\n", count);
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
		printf("type = %i\n", token_tab[i]->type);
		if (!token_tab[i]->type)
			get_buildin(token_tab[i]);
		printf("loop = %i\n", i);
		i++;
	}
	return (token_tab);
}
