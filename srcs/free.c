/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:19:05 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/01 13:39:52 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_node **tokens)
{
	int i;
	int j;

	i = 0;
	if (tokens)
	{
		while (tokens[i])
		{
			if (tokens[i]->input)
				free(tokens[i]->input);
			if (tokens[i]->ret)
				free(tokens[i]->ret);
			if (tokens[i]->arg)
			{
				j = 0;
				while (tokens[i]->arg[j])
				{
					free(tokens[i]->arg[j]);
					j++;
				}
				free(tokens[i]->arg);
			}
			free(tokens[i]);
			i++;
		}
		free(tokens);
	}
}
