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

	tmp = list;
	count = 0;
	while (tmp)
	{
		if (!strcmp(((t_var *)tmp->content)->var, ref))
			return (count);
		tmp = tmp->next;
		count++;
	}
	return (-1);
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
			if (ft_strrchr(arg[i], '=')) //&& (check_duplicate(*datas->env, arg[i]) < 0))
			{
				content = fill_tmp(arg[i]);
				new = ft_lstnew(content);
				ft_lstadd_back(datas->env, new);
				new = ft_lstnew(content);
				ft_lstadd_back(datas->export, new);
			}
			//else if (ft_strrchr(arg[i], '='))
			//{
			//	pos = check_duplicate(*datas->export, arg[i]);
			//	while (pos)
			//}
			else if (check_duplicate(*datas->export, arg[i]) < 0)
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
