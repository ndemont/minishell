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

void	delete_list(t_list *list)
{
	printf("str = %s\n", ((t_var *)list->content)->var);
	if (((t_var *)list->content)->var)
		free(((t_var *)list->content)->var);
	if (((t_var *)list->content)->value)
		free(((t_var *)list->content)->value);
	if (list)
		free(list);
}

void	delete_variable(int count, t_list *list)
{
	t_list *tmp;
	t_list *delete_me;
	int i;

	tmp = list;
	i = 0;
	while (i < count)
	{
		tmp = tmp->next;
		i++;
	}
	delete_me = tmp->next;
	printf("str = %s\n", ((t_var *)delete_me->content)->var);
	tmp->next = tmp->next->next;
	delete_list(delete_me);
}

void		check_duplicate(t_list *list, char *ref)
{
	t_list	*tmp;
	int		count;
	char *sub;
	int i;

	tmp = list;
	if (ft_strchr(ref, '='))
	{
		i = 0;
		while (ref[i] != '=')
			i++;
		sub = ft_substr(ref, 0, i);
	}
	else
		sub = ft_strdup(ref);
	count = 0;
	while (tmp)
	{
		if (!ft_strcmp(((t_var *)tmp->content)->var, sub))
		{
			delete_variable(count - 1, list);
			free(sub);
			return ;
		}
		tmp = tmp->next;
		count++;
	}
	free(sub);
	return ;
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
			printf("%s\n", arg[i]);
			check_duplicate(*datas->env, arg[i]);
			check_duplicate(*datas->export, arg[i]);
			if (ft_strrchr(arg[i], '='))
			{
				content = fill_tmp(arg[i]);
				new = ft_lstnew(content);
				ft_lstadd_back(datas->env, new);
				new = ft_lstnew(content);
				ft_lstadd_back(datas->export, new);
			}
			else
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
