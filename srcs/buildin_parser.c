/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:58:24 by ndemont           #+#    #+#             */
/*   Updated: 2021/03/31 12:06:48 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_arg(char *input, int *i)
{
	char	*arg;
	int 	j;

	arg = 0;
	while (input[*i] && input[*i] == ' ')
		*i = *i + 1;
	j = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\'' && input[*i] != '"')
		*i = *i + 1;
	if (input[*i] == '\'')
	{
		*i = *i + 1;
		while (input[*i] != '\'')
			*i = *i + 1;
	}
	else if (input[*i] == '"')
	{
		*i = *i + 1;
		while (input[*i] != '"')
			*i = *i + 1;
	}
	arg = ft_substr(input, j, *i - j);
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
	char	*list[8] = {"echo", "export", "env", "cd", "pwd", "unset", "exit", "$?"};
	int		i;
	int		j;
	int		count;

	(void)list;
	i = 0;
	j = 0;
	printf("token input = [%s]\n", token->input);
	count = count_arg(token->input);
	//printf("count = %i\n", count);
	if (count > 1)
	{
		token->arg = (char **)malloc(sizeof(char) * count);
		token->arg[count] = 0;
	}
	while (token->input[i])
	{
		if (!i)
			token->builtin = get_arg(token->input, &i);
		else
		{
			token->arg[j] = get_arg(token->input, &i);
			j++;
		}
		i++;
	}
	printf("Builtin = [%s]\n", token->builtin);
	if (token->arg)
	{
		i = 0;
		printf("Args =");
		while (token->arg[i])
		{
			printf("[%s]  ", token->arg[i]);
			i++;
		}
		printf("\n");
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
