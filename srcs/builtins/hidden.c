/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:36:01 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/15 14:36:10 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_split_on_equal(char *str)
{
	int i;
	char **arg;

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

void	add_to_hidden(char *line, t_big *datas)
{
	t_list *new;
	t_var *content;

	content = fill_tmp(line);
	new = ft_lstnew(content);
	ft_lstadd_back(datas->hidden, new);
}

void	actualize_env(char *line, t_big *datas)
{
	t_list *tmp;
	char **str;

	tmp = *datas->env;
	str = ft_split_on_equal(line);
	while (tmp && ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	free(((t_var *)tmp->content)->value);
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	free_double(str);
}

void	actualize_export(char *line, t_big *datas)
{
	t_list *tmp;
	char **str;

	tmp = *datas->export;
	str = ft_split_on_equal(line);
	while (tmp && ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	free(((t_var *)tmp->content)->value);
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	free_double(str);
}

void	actualize_hidden(char *line, t_big *datas)
{
	t_list *tmp;
	char **str;

	tmp = *datas->hidden;
	str = ft_split_on_equal(line);
	while (tmp && ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	free(((t_var *)tmp->content)->value);
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	free_double(str);
}

void	ft_hidden(char **arg, t_big *datas)
{
	int k;

	k = 0;
	while (arg[k])
	{
		if (!check_duplicate(*datas->hidden, arg[k]))
			add_to_hidden(arg[k], datas);
		else
		{
			actualize_hidden(arg[k], datas);
			if (check_duplicate(*datas->export, arg[k]))
				actualize_export(arg[k], datas);
			if (check_duplicate(*datas->env, arg[k]))
				actualize_env(arg[k], datas);
		}
		k++;
	}
}