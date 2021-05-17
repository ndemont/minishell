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

int	cmp_list(t_var *lst, t_var *lst2)
{
	return (ft_strcmp(lst->var, lst2->var));
}

int	store_export(char **env, t_big *datas)
{
	int		ret;
	int		k;
	t_list	**start;

	k = 0;
	start = store_first_elem(env[k]);
	if (!start)
		return (ERROR);
	datas->export = start;
	while (env[++k])
		ret = store_others_elem(env[k], start);
	if (!ret)
		return (ERROR);
	*start = ft_lst_sort(*start, &cmp_list);
	return (SUCCESS);
}

int	store_hidden(char **env, t_big *datas)
{
	int		ret;
	int		k;
	t_list	**start;

	k = 0;
	start = store_first_elem(env[k]);
	if (!start)
		return (ERROR);
	datas->hidden = start;
	while (env[++k])
		ret = store_others_elem(env[k], start);
	if (!ret)
		return (ERROR);
	return (SUCCESS);
}

int	store_env(char **env, t_big *datas)
{
	int		ret;
	int		k;
	t_list	**start;

	k = 0;
	start = store_first_elem(env[k]);
	if (!start)
		return (ERROR);
	datas->env = start;
	while (env[++k])
		ret = store_others_elem(env[k], start);
	if (!ret || !store_export(env, datas) || !store_hidden(env, datas) || \
	!shell_lvl(datas))
		return (ERROR);
	return (SUCCESS);
}

int	ft_env(char **av, t_big *datas)
{
	t_list	*tmp;

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
