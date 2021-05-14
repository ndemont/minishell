/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:22:53 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/14 15:24:12 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_arg(char *input)
{
	int count;
	int	newword;
	int i;

	count = 0;
	i = 0;
	if (!input[0])
		return (0);
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
		while (input[i] && input[i] != ' ' && input[i] != '\'' && input[i] != '"' && input[i] != '\t' && input[i] != '\\')
			i++;
		if (input[i] == '\\' && input[i + 1])
			i += 2;
		else if (input[i] == '\'')
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
