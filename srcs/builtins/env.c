/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:41:48 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/06 14:43:23 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		change_shell_lvl(t_list *tmp)
{
	int lvl;
	char *level;
	t_var *tmp2;
	t_list *new;

	lvl = 0;
	level = NULL;
	tmp2 = NULL;
	while (tmp && ft_strcmp(((t_var *)(tmp->content))->var, "SHLVL"))
		tmp = tmp->next;
	if (!ft_strcmp(((t_var *)(tmp->content))->var, "SHLVL"))
	{
		lvl = ft_atoi(((t_var *)(tmp->content))->value);
		lvl++;
		if (((t_var *)(tmp->content))->value)
			free(((t_var *)(tmp->content))->value);
		if (!(level = ft_itoa(lvl)))
			return (0);
		if (!(((t_var *)(tmp->content))->value = ft_strdup(level)))
			return (0);
	}
	else
	{
		if (!(tmp2 = (t_var *)malloc(sizeof(t_var))))
			return (0);
		tmp2->var = NULL;
		tmp2->value = NULL;
		lvl++;
		if (!(level = ft_itoa(lvl)))
			return (0);
		if (!(tmp2->var = ft_strdup("SHLVL")))
			return (0);
		if (!(tmp2->value = ft_strdup(level)))
			return (0);
		if (!(new = ft_lstnew(tmp2)))	
			return(0);
		ft_lstadd_back(&tmp, new);
	}
	if (level)
		free(level);
	return (1);
}

int		shell_lvl(t_big *datas)
{
	if (!change_shell_lvl(*datas->env))
		return (0);
	if (!change_shell_lvl(*datas->export))
		return (0);
	if (!change_shell_lvl(*datas->hidden))
		return (0);
	return (1);
}

t_var	*fill_tmp(char *str)
{
	int i;
	t_var *tmp;

	i = 0;
	if (!(tmp = (t_var *)malloc(sizeof(t_var))))
		return (0);
	tmp->var = NULL;
	tmp->value = NULL;
	while(str[i] && str[i] != '=')
		i++;
	if (!(tmp->var = ft_substr(str, 0, i)))
	{
		free(tmp);
		return (0);
	}
	if (str[i] == '=')
		i++;
	if (!(tmp->value = ft_substr(str, i, (ft_strlen(str) - i))))
	{
		free(tmp->var);
		free(tmp);
		return (0);
	}
	return (tmp);
}

int		cmp_list(t_var *lst, t_var *lst2)
{
	return (ft_strcmp(lst->var, lst2->var));
}

int		store_export(char **env, t_big *datas)
{
	int k;
	void *content;
	t_list *tmp;
	t_list **start;

	k = 0;
	if (!(start = (t_list **)malloc(sizeof(t_list))))
		return (0);
	if (!(content = fill_tmp(env[k])))
	{
		free(start);
		return (0);
	}
	if (!(*start = ft_lstnew(content)))
	{
		free(content);
		free(start);
		return (0);
	}
	datas->export = start;
	while (env[++k])
	{
		if (!(content = fill_tmp(env[k])))
			return (0);
		if (!(tmp = ft_lstnew(content)))
		{
			free(content);
			return (0);
		}
		ft_lstadd_back(start, tmp);
	}
	*start = ft_lst_sort(*start, &cmp_list);
	return (1);
}

int		store_hidden(char **env, t_big *datas)
{
	int k;
	void *content;
	t_list *tmp;
	t_list **start;

	k = 0;
	if (!(start = (t_list **)malloc(sizeof(t_list))))
		return (0);
	if (!(content = fill_tmp(env[k])))
	{
		free(start);
		return (0);
	}
	if (!(*start = ft_lstnew(content)))
	{
		free(start);
		free(content);
		return (0);
	}
	datas->hidden = start;
	while (env[++k])
	{
		if (!(content = fill_tmp(env[k])))
			return (0);
		if (!(tmp = ft_lstnew(content)))
			return (0);
		ft_lstadd_back(start, tmp);
	}
	return (1);
}

int		store_env(char **env, t_big *datas)
{
	int k;
	void *content;
	t_list *tmp;
	t_list **start;

	k = 0;
	if (!(start = (t_list **)malloc(sizeof(t_list))))
		return (0);
	if (!(content = fill_tmp(env[k])))
	{
		free(start);
		return (0);
	}
	if (!(*start = ft_lstnew(content)))
	{
		free(content);
		free(start);
		return (0);
	}
	datas->env = start;
	while (env[++k])
	{
		content = fill_tmp(env[k]);
		tmp = ft_lstnew(content);
		ft_lstadd_back(start, tmp);
	}
	if (!store_export(env, datas) || !store_hidden(env, datas) || !shell_lvl(datas))
		return (0);
	return (1);
}

int		ft_env(char **av, t_big *datas)
{

	t_list *tmp;

	if (av && *av && av[1])
	{
		tcaps.ret = RET_ERROR;
		printf("env: %s: No such file or directory\n", av[1]);
		return (127);
	}
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