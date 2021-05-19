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

int	actualize_export_actualize_env(char *line, t_big *datas)
{
	t_list	*tmp;
	char	**str;

	tmp = *datas->env;
	str = ft_split_on_equal(line);
	if (!str)
		return (ERROR);
	while (ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	clean_free(&(((t_var *)tmp->content)->value));
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	if (!(((t_var *)tmp->content)->value))
	{
		free_double(str);
		return (printi_stderr(0, strerror(errno), 0));
	}
	tmp = *datas->export;
	while (ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	clean_free(&(((t_var *)tmp->content)->value));
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	free_double(str);
	if (!(((t_var *)tmp->content)->value))
		return (printi_stderr(0, strerror(errno), 0));
	return (SUCCESS);
}

int	add_hidden_add_export_add_env(char *line, t_big *datas)
{
	int	ret;
	int	ret2;
	int	ret3;

	ret = add_to_list(line, datas->env);
	ret2 = add_to_list(line, datas->export);
	ret3 = add_to_list(line, datas->hidden);
	if (!ret || !ret2 || !ret3)
		return (ERROR);
	else
		return (SUCCESS);
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
		free_elems_print_error(&content->var, &content);
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

int	treat_list(char *arg, t_big *datas)
{
	int	ret;
	int	ret2;
	int	ret3;
	int	ret_final;

	ret = actualize_list(arg, *datas->hidden);
	ret2 = check_duplicate(*datas->export, arg);
	ret3 = check_duplicate(*datas->env, arg);
	ret_final = SUCCESS;
	if (!ret || ret2 == ERR || ret3 == ERR)
		return (ERROR);
	if (ret2 && !ret3)
		ret_final = actualize_export_add_env(arg, datas);
	else if (ret2 && ret3)
		ret_final = actualize_export_actualize_env(arg, datas);
	else if (!ret2)
		ret_final = add_hidden_to_env_export(arg, datas);
	if (!ret_final)
		return (ERROR);
	else
		return (SUCCESS);
}
