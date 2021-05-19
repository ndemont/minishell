/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list_actualization_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:44:30 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/19 11:44:38 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*create_content_and_dup(char *str, char *str2)
{
	t_var	*content;

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

int	create_and_add_new_elem(char *line, t_big *datas, t_list *tmp)
{
	t_var	*content;

	content = fill_tmp(line);
	if (!content)
		return (ERROR);
	tmp = ft_lstnew(content);
	if (!tmp)
		return (printi_stderr(0, strerror(errno), 0));
	ft_lstadd_back(datas->env, tmp);
	return (SUCCESS);
}

int	actualize_export_add_env(char *line, t_big *datas)
{
	t_list	*tmp;
	char	**str;

	tmp = *datas->export;
	str = ft_split_on_equal(line);
	if (!str)
		return (ERROR);
	while (tmp && ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	clean_free(&(((t_var *)tmp->content)->value));
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	free_double(str);
	if (!(((t_var *)tmp->content)->value))
		return (printi_stderr(0, strerror(errno), 0));
	return (create_and_add_new_elem(line, datas, tmp));
}
