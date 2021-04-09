/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:58:24 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/09 12:34:09 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_quote(char *input, int *i, int *j)
{
	char *arg;

	arg = 0;
	if (input[*i] == '\'')
	{
		*i = *i + 1;
		while (input[*i] != '\'')
			*i = *i + 1;
		arg = ft_substr(input, *j + 1, *i - *j - 1);
		if (!arg)
			return (0);
		*i = *i + 1;
	}
	else if (input[*i] == '"')
	{
		*i = *i + 1;
		while (input[*i] != '"')
			*i = *i + 1;
		arg = ft_substr(input, *j + 1, *i - *j - 1);
		if (!arg)
			return (0);
		*i = *i + 1;
	}
	return (arg);
}

char	*get_arg(char *input, int *i)
{
	char	*arg;
	char	*tmp1;
	char	*tmp2;
	int		j;

	arg = malloc(sizeof(char));
	arg[0] = '\0';
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		*i = *i + 1;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t')
	{
		j = *i;
		while (input[*i] && input[*i] != ' ' && input[*i] != '\'' && input[*i] != '"' && input[*i] != '\t')
			*i = *i + 1;
		tmp1 = arg;
		if (input[j] == '\'' || input[j] == '"')
		{
			tmp2 = get_quote(input, i, &j);
			if (!tmp2)
				print_errors(strerror(errno));
		}
		else
		{
			tmp2 = ft_substr(input, j, *i - j);
			if (!tmp2)
				print_errors(strerror(errno));
		}
		arg = ft_strjoin(tmp1, tmp2);
		free(tmp1);
		free(tmp2);
	}
	return (arg);
}

int	count_arg(char *input)
{
	int count;
	int	newword;
	int i;

	count = 0;
	i = 0;
	while (input[i])
	{
		newword = 0;
		if (!i)
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
				i++;
		else
		{
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			{
				if (!newword)
					newword = 1;
				i++;
			}
			if (input[i])
				count += newword;
		}
		if (!input[i])
			break ;
		while (input[i] && input[i] != ' ' && input[i] != '\'' && input[i] != '"' && input[i] != '\t')
			i++;
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'')
				i++;
			i++;
		}
		else if (input[i] == '"')
		{
			i++;
			while (input[i] != '"')
				i++;
			i++;
		}
		else if (!input[i])
			break ;
	}
	count++;
	return (count);
}

void	get_builtin(t_node *token)
{
	static char	*list[8] = {"echo", "export", "env", "cd", "pwd", "unset", "exit", "$?"};
	int		i;
	int		j;
	int		count;

	i = 0;
	count = count_arg(token->input);
	token->arg = (char **)malloc(sizeof(char *) * (count + 1));
	if (!token->arg)
		print_errors(strerror(errno));
	j = 0;
	while (token->input[i] && j < count)
	{
		token->arg[j] = get_arg(token->input, &i);
		j++;
	}
	token->arg[count] = 0;
	token->command = token->arg[0];
	i = 0;
	while (i < 8)
	{
		if (!ft_strcmp(list[i], token->arg[0]))
		{
			token->builtin = token->arg[0];
			token->command = 0;
			break ;
		}
		i++;
	}
	printf("\nBuiltin = [%s]\n", token->builtin);
	printf("Command = [%s]\n", token->command);
	if (token->arg)
	{
		i = 0;
		printf("Args = ");
		while (token->arg[i])
		{
			printf("[%s] ", (char *)token->arg[i]);
			i++;
		}
		printf("\n");
	}
	printf("\n");
}

t_node	**ft_builtin_parser(t_node **token_tab)
{
	int i;

	i = 0;
	printf("\nLEXER");
	printf("\n-----");
	while (token_tab[i])
	{
		if (!token_tab[i]->type)
			get_builtin(token_tab[i]);
		i++;
	}
	if (token_tab[i - 1]->type)
		print_errors("Missing command at end of line");
	return (token_tab);
}
