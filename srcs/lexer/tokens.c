/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:32:08 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/20 19:06:51 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_grammar(char *str, int i)
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

int	ft_is_quote(char *input, int i)
{
	int	j;

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
		{
			if (input[j] == '\\' && input[j + 1] == '"')
				j++;
			j++;
		}
		if (input[j] == '"')
			return (j + 1);
		else
			return (-1);
	}
	return (0);
}

int	ft_check_char(int *i, int *j, char *input)
{
	int	type;

	while (input[*i] && !ft_is_grammar(input, *i) && \
		!ft_is_quote(input, *i) && input[*i] != '\\')
		*i = *i + 1;
	type = ft_is_grammar(input, *i);
	if (input[*i] == '\\' && input[*i + 1])
		*i = *i + 2;
	else if (input[*i] == '\\' && !input[*i + 1])
		return (-1);
	else if (type > 0)
	{
		if (type == 2)
			*i = *i + 1;
		*i = *i + 1;
		*j = *j + 1;
	}
	else if (ft_is_quote(input, *i) > 0)
		*i = ft_is_quote(input, *i);
	else if (ft_is_quote(input, *i) < 0)
		return (-1);
	return (type);
}

int	ft_count_tokens(char *input)
{
	int	i;
	int	j;
	int	type;

	i = 0;
	j = 0;
	type = 0;
	while (input[i])
	{
		type = ft_check_char(&i, &j, input);
		if (type == -1)
			return (-1);
	}
	if (!i)
		return (0);
	if (type == 5)
		return (j * 2);
	return ((j * 2) + 1);
}
