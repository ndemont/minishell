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

t_var	*create_content_and_dup(char *str, char *str2)
{
	t_var *content;

	content = (t_var *)malloc(sizeof(t_var));
	if (!content)
	{
		printi_stderr(0, strerror(errno), 0);
		return (0);
	}
	content->var = ft_strdup(str);
	if (!content->var)
	{
		free(content);
		printi_stderr(0, strerror(errno), 0);
		return (0);
	}
	content->value = ft_strdup(str2);
	if (!content->value)
	{
		free(content->var);
		free(content);
		printi_stderr(0, strerror(errno), 0);
		return (0);
	}
	return (content);
}

int	add_to_both_list(t_var **content, t_var **content2, t_big *datas)
{
	t_list	*tmp;

	tmp = ft_lstnew(*content);
	if (!tmp)
	{
		free(*content);
		return (printi_stderr(0, strerror(errno), 0));
	}
	ft_lstadd_back(datas->export, tmp);
	tmp = ft_lstnew(*content2);
	if (!tmp)
	{
		free(*content2);
		return (printi_stderr(0, strerror(errno), 0));
	}
	ft_lstadd_back(datas->env, tmp);
	return (SUCCESS);
}

int	add_hidden_to_env_export(char *line, t_big *datas)
{
	t_list	*hidden;
	t_var	*content;
	t_var	*content2;

	hidden = *datas->hidden;
	while (hidden && ft_strcmp(line, ((t_var *)hidden->content)->var))
		hidden = hidden->next;
	content = create_content_and_dup(((t_var *)hidden->content)->var, \
	((t_var *)hidden->content)->value);
	if (!content)
		return (ERROR);
	content2 = create_content_and_dup(((t_var *)hidden->content)->var, \
	((t_var *)hidden->content)->value);
	if (!content2)
	{
		free(content);
		return (ERROR);
	}
	return (add_to_both_list(&content, &content2, datas));
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

t_list	*create_content_value_zero(char *line)
{
	t_list	*new;
	t_var	*content;

	content = (t_var *)malloc(sizeof(t_var));
	if (!content)
	{
		printi_stderr(0, strerror(errno), 0);
		return (ERROR);
	}
	content->var = ft_strdup(line);
	if (!content->var)
	{
		free(content);
		printi_stderr(0, strerror(errno), 0);
		return (ERROR);
	}
	content->value = 0;
	new = ft_lstnew(content);
	if (!new)
	{
		free(content->var);
		free(content);
		printi_stderr(0, strerror(errno), 0);
		return (ERROR);
	}
	return (new);
}

int	add_hidden_add_export(char *line, t_big *datas)
{
	t_list	*new;

	new = create_content_value_zero(line);
	if (!new)
		return (ERROR);
	ft_lstadd_back(datas->export, new);
	new = create_content_value_zero(line);
	if (!new)
		return (ERROR);
	ft_lstadd_back(datas->hidden, new);
	return (SUCCESS);
}
