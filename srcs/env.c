/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:41:48 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/09 17:07:27 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*fill_tmp(char *str)
{
	int i;
	t_var *tmp;

	i = 0;
	tmp = (t_var *)malloc(sizeof(t_var));
	tmp->var = NULL;
	tmp->value = NULL;
	while(str[i] && str[i] != '=')
		i++;
	tmp->var = ft_substr(str, 0, i);
	i++;
	tmp->value = ft_substr(str, i, (ft_strlen(str) - i));
	return (tmp);
}

void	store_env(char **env, t_big *datas)
{
	int k;
	void *content;
	t_list *tmp;
	t_list **start;

	k = 0;
	start = (t_list **)malloc(sizeof(t_list));
	content = fill_tmp(env[k]);
	*start = ft_lstnew(content);
	while (env[++k])
	{
		content = fill_tmp(env[k]);
		tmp = ft_lstnew(content);
		ft_lstadd_back(start, tmp);
	}
	datas->env = start;
}

int		ft_env(t_big *datas)
{

	t_list *tmp;

	tmp = *(datas->env);
	while (tmp)
	{
		ft_putstr(((t_var *)tmp->content)->var);
		ft_putchar('=');
		ft_putstr(((t_var *)tmp->content)->value);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	return (0);
}