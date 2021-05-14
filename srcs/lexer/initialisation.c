/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:07:14 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/14 16:11:05 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_init_grammar_node(int type)
{
	t_node *new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
	{
		printc_stderr(0, strerror(errno), 0);
		return (0);
	}
	new->type = type;
	new->input = 0;
	new->arg = 0;
	new->builtin = 0;
	new->command = 0;
	new->left = 0;
	new->right = 0;
	return (new);
}

t_node	*ft_init_buildin_node(char *input, int type)
{
	t_node *new;

	if (!input)
	{
		printc_stderr(0, strerror(errno), 0);
		return (0);
	}
	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
	{
		free(input);
		printc_stderr(0, strerror(errno), 0);
		return (0);
	}
	new->type = type;
	new->input = input;
	new->arg = 0;
	new->builtin = 0;
	new->left = 0;
	new->right = 0;
	return (new);
}
