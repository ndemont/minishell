/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:22:53 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/25 21:55:04 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_isspace(char *input, int *i, int count)
{
	if (!(*i))
	{
		while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
			*i = *i + 1;
	}
	else
	{
		while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
			*i = *i + 1;
		if (input[*i])
			count++;
	}
	return (count);
}

void	count_special_char(char *input, int *i)
{
	if (input[*i] == '\\' && input[*i + 1])
		*i = *i + 2;
	else if (input[*i] == '\'')
	{
		*i = *i + 1;
		while (input[*i] != '\'')
			*i = *i + 1;
		*i = *i + 1;
	}
	else if (input[*i] == '"')
	{
		*i = *i + 1;
		while (input[*i] && input[*i] != '"')
		{
			if (input[*i] == '\\')
				*i = *i + 2;
			else
				*i = *i + 1;
		}
		if (input[*i])
			*i = *i + 1;
	}
}

int	count_arg(char *input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (input && !input[0])
		return (0);
	while (input && input[i])
	{
		count = skip_isspace(input, &i, count);
		if (!input[i])
			break ;
		while (input[i] && input[i] != ' ' && input[i] != '\'' && \
		input[i] != '"' && input[i] != '\t' && input[i] != '\\')
			i++;
		if (!input[i])
			break ;
		count_special_char(input, &i);
	}
	count++;
	return (count);
}
