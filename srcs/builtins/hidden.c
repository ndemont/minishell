/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:36:01 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/06 11:33:53 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_on_equal(char *str)
{
	int		i;
	char	**arg;

	i = 0;
	arg = (char **)malloc(sizeof(char *) * 3);
	while (str[i] && str[i] != '=')
		i++;
	arg[0] = ft_substr(str, 0, i);
	if (str[i] == '=')
		i++;
	arg[1] = ft_substr(str, i, ft_strlen(str) - i);
	arg[2] = 0;
	return (arg);
}

void	add_to_list(char *line, t_list **list)
{
	t_list	*new;
	t_var	*content;

	content = fill_tmp(line);
	new = ft_lstnew(content);
	ft_lstadd_back(list, new);
}

void	actualize_list(char *line, t_list *list)
{
	t_list	*tmp;
	char	**str;

	tmp = list;
	str = ft_split_on_equal(line);
	while (tmp && ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	free(((t_var *)tmp->content)->value);
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	free_double(str);
}

int		ft_hidden(char **arg, t_big *datas)
{
	int k;

	k = 0;
	while (arg[k])
	{
		if (!check_duplicate(*datas->hidden, arg[k]))
			add_to_list(arg[k], datas->hidden);
		else
		{
			actualize_list(arg[k], *datas->hidden);
			if (check_duplicate(*datas->export, arg[k]))
				actualize_list(arg[k], *datas->export);
			if (check_duplicate(*datas->env, arg[k]))
				actualize_list(arg[k], *datas->env);
		}
		k++;
	}
	return (0);
}
