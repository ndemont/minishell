/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:00:09 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/06 11:30:14 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_elem(t_list *elem)
{
	if (elem)
	{
		if (elem->content)
		{
			if (((t_var *)elem->content)->var)
			{
				free(((t_var *)elem->content)->var);
				((t_var *)elem->content)->var = 0;
			}
			if (((t_var *)elem->content)->value)
			{
				free(((t_var *)elem->content)->value);
				((t_var *)elem->content)->value = 0;
			}
			free(elem->content);
			elem->content = 0;
		}
		free(elem);
		elem = 0;
	}
}

int		ft_lst_remove(t_list **list, char *var)
{
	int count;
	t_list	*lst;
	t_list	*del_me;
	t_list	*previous;

	count = 0;
	lst = *list;
	while (lst)
	{
		if (!ft_strcmp(((t_var *)lst->content)->var, var) && !count)
		{
			del_me = lst;
			lst = del_me->next;
			*list = lst;
			ft_delete_elem(del_me);
		}
		else if (!ft_strcmp(((t_var *)lst->content)->var, var) && count)
		{
			del_me = lst;
			lst = del_me->next;
			ft_delete_elem(del_me);
			previous->next = lst;
		}
		previous = lst;
		if (lst)
			lst = lst->next;
		count++;
	}
	return (1);
}

int		ft_unset(char **arg, t_big *datas)
{
	int i;

	i = 1;
	while (arg[i])
	{
		ft_lst_remove(datas->env, arg[i]);
		ft_lst_remove(datas->export, arg[i]);
		ft_lst_remove(datas->hidden, arg[i]);
		i++;
	}
	return (0);
}
