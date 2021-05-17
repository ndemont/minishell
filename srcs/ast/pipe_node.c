/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 23:32:55 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/17 23:46:03 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_node(t_node **tokens, t_big *datas, int i)
{
	if (i == 0)
		datas->root = tokens[i];
	else
	{
		tokens[i]->left = datas->root;
		datas->root = tokens[i];
	}
}
