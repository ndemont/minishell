/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:59:15 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/19 15:04:23 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	actualize_variables(t_big *datas)
{
	int	ret1;
	int	ret2;
	int	ret3;

	ret1 = cd_actualize_env(datas->env);
	ret2 = cd_actualize_env(datas->export);
	ret3 = cd_actualize_env(datas->hidden);
	if (!ret1 || !ret2 || !ret3)
		return (ERROR);
	else
		return (SUCCESS);
}

int	come_back_home(t_list *tmp)
{
	int	ret;

	ret = 0;
	while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "HOME"))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(((t_var *)tmp->content)->var, "HOME"))
	{
		ret = chdir(((t_var *)tmp->content)->value);
		if (ret == ERR)
			return (printi_stderr("cd", strerror(errno), 1));
		return (SUCCESS);
	}
	else
		return (printi_stderr("cd", "HOME not set", 1));
}

int	previous_path(t_list *tmp)
{
	int	ret;

	ret = 0;
	while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "OLDPWD"))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(((t_var *)tmp->content)->var, "OLDPWD"))
	{
		ret = chdir(((t_var *)tmp->content)->value);
		if (ret == ERR)
			return (printi_stderr("cd", strerror(errno), 1));
		ft_putstr(((t_var *)tmp->content)->value);
		ft_putchar('\n');
		return (SUCCESS);
	}
	else
		return (printi_stderr("cd", "OLDPWD not set", 1));
}

int	get_regular_path(char **arg, t_list *tmp)
{
	int	ret;

	ret = 1;
	if (!ft_strcmp(arg[1], "-"))
		previous_path(tmp);
	else
	{
		ret = chdir(arg[1]);
		if (ret == ERR)
			return (printi_stderr("cd", strerror(errno), 1));
	}
	return (1);
}

int	ft_cd(char **arg, t_big *datas)
{
	int		ret;
	t_list	*tmp;
	char	*home;

	tmp = *datas->env;
	ret = 1;
	while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "HOME"))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(((t_var *)tmp->content)->var, "HOME"))
		home = ft_strdup(((t_var *)tmp->content)->value);
	if (!arg[1] || (home && !ft_strcmp(arg[1], home)))
		come_back_home(tmp);
	else
		ret = get_regular_path(arg, tmp);
	if (!ret)
		return (0);
	ret = actualize_variables(datas);
	if (!ret)
		return (BUILT_IN_FAILURE);
	g_tcaps.current_dir = getcwd(0, 0);
	g_tcaps.current_dir = ft_strrchr(g_tcaps.current_dir, '/');
	return (0);
}
