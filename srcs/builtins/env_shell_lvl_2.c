/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:41:47 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/17 14:41:48 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	increment_shell_lvl(char **level, t_list *tmp)
{
	int	lvl;

	lvl = ft_atoi(((t_var *)(tmp->content))->value);
	lvl++;
	if (((t_var *)(tmp->content))->value)
		free(((t_var *)(tmp->content))->value);
	*level = ft_itoa(lvl);
	if (!(*level))
		return (printi_stderr(0, strerror(errno), 0));
	((t_var *)(tmp->content))->value = ft_strdup(*level);
	if (!(((t_var *)(tmp->content))->value))
	{
		clean_free(level);
		return (printi_stderr(0, strerror(errno), 0));
	}
	return (1);
}

void	clean_if_mallocked(char **level, char **var, char **value)
{
	clean_free(level);
	clean_free(var);
	clean_free(value);
}
