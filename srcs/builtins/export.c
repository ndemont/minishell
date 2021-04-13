/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 19:15:06 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/12 23:23:58 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_duplicate(t_list *list, char *ref)
{
	t_list	*tmp;
	int		count;
	char *str;
	int i;

 	i = 0;
	while (ref [i] && ref[i] != '=')
		i++;
	str = ft_substr(ref, 0, i);
	tmp = list;
	count = 0;
	while (tmp)
	{
		if (!ft_strcmp(((t_var *)tmp->content)->var, str))
		{
			free(str);
			return (1);
		}
		tmp = tmp->next;
		count++;
	}
	free(str);
	return (0);
}

void	actualize_env_export(char *line, t_big *datas)
{
	t_list *tmp;
	char **str;
	t_var *content;
	int i;

	i = 0;
	tmp = *datas->export;
	str = ft_split(line, '=');
	ft_putstr(str[0]);
	while (ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	content = fill_tmp(line);
	tmp = ft_lstnew(content);
	ft_lstadd_back(datas->env, tmp);
	free_double(str);	
}

void	actualize_var(char *line, t_big *datas)
{
	t_list *tmp;
	char **str;
	int i;

	i = 0;
	tmp = *datas->env;
	str = ft_split(line, '=');
	while (ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	free(((t_var *)tmp->content)->value);
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	tmp = *datas->export;
	while (ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	free(((t_var *)tmp->content)->value);
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	free_double(str);
}

int		ft_export(char **arg, t_big *datas)
{
	t_list	*tmp;
	t_var	*content;
	t_list	*new;
	int		i;
	//int		pos;

	i = 1;
	if (!arg[i])
	{
		tmp = *(datas->export);
		while (tmp)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(((t_var *)tmp->content)->var, STDOUT_FILENO);
			if (((t_var *)tmp->content)->value)
			{
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putstr_fd(((t_var *)tmp->content)->value, STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
			tmp = tmp->next;
		}
	}
	else
	{
		while (arg[i])
		{
			printf("retour Strchr = %d | retour check_duplicate = %d\n", ft_strchr(arg[i], '='), check_duplicate(*datas->export, arg[i]));
			if ((ft_strchr(arg[i], '=')) && !check_duplicate(*datas->env, arg[i]) && !check_duplicate(*datas->export, arg[i]))
			{
				content = fill_tmp(arg[i]);
				new = ft_lstnew(content);
				ft_lstadd_back(datas->env, new);
				new = ft_lstnew(content);
				ft_lstadd_back(datas->export, new);
			}
			else if ((ft_strchr(arg[i], '=')) && check_duplicate(*datas->env, arg[i]))
				actualize_var(arg[i], datas);
			else if ((ft_strchr(arg[i], '=')) && check_duplicate(*datas->export, arg[i]))
				actualize_env_export(arg[i], datas);
			else if ((!ft_strchr(arg[i], '=')) && !check_duplicate(*datas->export, arg[i]))
			{
				content = (t_var *)malloc(sizeof(t_var));
				content->var = ft_strdup(arg[i]);
				content->value = 0;
				new = ft_lstnew(content);
				ft_lstadd_back(datas->export, new);
			}
			i++;
		}
	}
	*datas->export = ft_lst_sort(*datas->export, &cmp_list);
	return (0);
}
