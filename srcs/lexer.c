/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 13:06:25 by ndemont           #+#    #+#             */
/*   Updated: 2021/03/26 13:26:15 by ndemont          ###   ########.fr       */
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

void	ft_lexer(char *input)
{
	int i;
	int j;

	i = 0;
	while (input[i])
	{
		while (input[j] && input[j] == ' ')
			i++;
		j = i;
		while (input[j] && !ft_is_grammar(input, j))
			j++;
		
	}
		
}