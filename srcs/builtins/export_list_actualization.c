/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:08:25 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/18 11:08:33 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_hidden_to_env_export(char *line, t_big *datas)
{
	t_list	*hidden;
	t_list	*tmp;
	t_var	*content;
	t_var	*content2;

	hidden = *datas->hidden;
	while (hidden && ft_strcmp(line, ((t_var *)hidden->content)->var))
		hidden = hidden->next;
	content = (t_var *)malloc(sizeof(t_var));
	content->var = ft_strdup(((t_var *)hidden->content)->var);
	content->value = ft_strdup(((t_var *)hidden->content)->value);
	content2 = (t_var *)malloc(sizeof(t_var));
	content2->var = ft_strdup(((t_var *)hidden->content)->var);
	content2->value = ft_strdup(((t_var *)hidden->content)->value);
	tmp = ft_lstnew(content);
	ft_lstadd_back(datas->export, tmp);
	tmp = ft_lstnew(content2);
	ft_lstadd_back(datas->env, tmp);
}

void	actualize_export_add_env(char *line, t_big *datas)
{
	t_list	*tmp;
	char	**str;
	t_var	*content;

	tmp = *datas->export;
	str = ft_split_on_equal(line);
	while (ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	clean_free(&(((t_var *)tmp->content)->value));
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	content = fill_tmp(line);
	tmp = ft_lstnew(content);
	ft_lstadd_back(datas->env, tmp);
	free_double(str);
}

void	actualize_export_actualize_env(char *line, t_big *datas)
{
	t_list	*tmp;
	char	**str;

	tmp = *datas->env;
	str = ft_split_on_equal(line);
	while (ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	clean_free(&(((t_var *)tmp->content)->value));
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	tmp = *datas->export;
	while (ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	clean_free(&(((t_var *)tmp->content)->value));
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	free_double(str);
}

void	add_hidden_add_export_add_env(char *line, t_big *datas)
{
	add_to_list(line, datas->env);
	add_to_list(line, datas->export);
	add_to_list(line, datas->hidden);
}

void	add_hidden_add_export(char *line, t_big *datas)
{
	t_var	*content;
	t_list	*new;

	content = (t_var *)malloc(sizeof(t_var));
	content->var = ft_strdup(line);
	content->value = 0;
	new = ft_lstnew(content);
	ft_lstadd_back(datas->export, new);
	content = (t_var *)malloc(sizeof(t_var));
	content->var = ft_strdup(line);
	content->value = 0;
	new = ft_lstnew(content);
	ft_lstadd_back(datas->hidden, new);
}
