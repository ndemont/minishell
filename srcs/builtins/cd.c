/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:59:15 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/06 11:18:45 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	actualize_env(t_list **lst)
{
	t_list	*tmp;
	char	*current_pwd;
	char	*oldpwd;
	int		pwd_flag;

	tmp = *lst;
	current_pwd = NULL;
	oldpwd = NULL;
	pwd_flag = 0;
	while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "PWD"))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(((t_var *)tmp->content)->var, "PWD"))
	{
		current_pwd = getcwd(current_pwd, 0);
		if (((t_var *)tmp->content)->value)
		{
			pwd_flag = 1;
			oldpwd = ft_strdup(((t_var *)tmp->content)->value);
		}
		if (current_pwd)
		{
			if (((t_var *)tmp->content)->value)
				free(((t_var *)tmp->content)->value);
			((t_var *)tmp->content)->value = ft_strdup(current_pwd);
		}
	}
	if (pwd_flag)
	{
		tmp = *lst;
		while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "OLDPWD"))
			tmp = tmp->next;
		if (tmp && !ft_strcmp(((t_var *)tmp->content)->var, "OLDPWD"))
		{
			if (((t_var *)tmp->content)->value)
				free(((t_var *)tmp->content)->value);
			if (oldpwd)
				((t_var *)tmp->content)->value = ft_strdup(oldpwd);
		}
	}
	if (oldpwd)
		free(oldpwd);
	if (current_pwd)
		free(current_pwd);
}

void	actualize_variables(t_big *datas)
{
	actualize_env(datas->env);
	actualize_env(datas->export);
	actualize_env(datas->hidden);
}

int		ft_cd(char **arg, t_big *datas)
{
	t_list *tmp;

	tmp = *datas->env;
	if (!arg[1] || !ft_strcmp(arg[1], "~"))
	{
		while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "HOME"))
			tmp = tmp->next;
		if (tmp && !ft_strcmp(((t_var *)tmp->content)->var, "HOME"))
			chdir(((t_var *)tmp->content)->value);
		else
		{
			ft_putstr("minishellrose: cd: HOME not set\n"); //ECRIRE SUR LE STDOUT, MAIS BREAK MEME SI PIPE 
			return (1);
		}
	}
	else
	{
		if (!ft_strcmp(arg[1], "-"))
		{
			while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "OLDPWD"))
				tmp = tmp->next;
			if (tmp && !ft_strcmp(((t_var *)tmp->content)->var, "OLDPWD"))
			{
				chdir(((t_var *)tmp->content)->value);
				ft_putstr(((t_var *)tmp->content)->value);
				ft_putchar('\n');
			}
			else
			{
				ft_putstr("minishellrose: cd: OLDPWD not set\n"); //ECRIRE SUR LE STDOUT, MAIS BREAK MEME SI PIPE 
				return (1);
			}
		}
		else
		{
			if (chdir(arg[1]) < 0)
			{
				printf("minishellrose: cd: %s: No such file or directory\n", arg[1]);
				return (1);
			}
		}
	}
	actualize_variables(datas);
	return (0);	
}
