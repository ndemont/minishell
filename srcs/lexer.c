/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 13:06:25 by ndemont           #+#    #+#             */
/*   Updated: 2021/03/26 15:20:49 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_grammar(char *str, int i)
{
	if (str[i] == '|')
		return (1);
	else if (str[i] == '>')
	{
		if (str[i + 1] && str[i + 1] == '>')
			return (2);
		else
			return (1);
	}
	else if (str[i] == '<')
		return (1);
	else if (str[i] == ';')
		return (1);
	else
		return (0);
}

int 	ft_is_quote(char *input, int i)
{
	int j;

	if (input[i] == '\'')
	{
		j = i;
		while (input[j] && input[i] != '\'')
			j++;
		if (input[i] == '\'')
			return (j - i);
		else
			return (-1);
	}
	if (input[i] == '"')
	{
		j = i;
		while (input[j] && input[i] != '"')
			j++;
		if (input[i] == '"')
			return (j - i);
		else
			return (-1);
	}
	return (0);
}

void	ft_lexer(char *input)
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
			i += ft_is_grammar(input, i);
			j++;
		}
		else if (ft_is_quote(input, i))
			i+= ft_is_quote(input, i);
		else
			break ;
	}
	write(1, "token numbers = ", 16);
	write(1, &j, 4);
	write(1, "\n", 1);
}