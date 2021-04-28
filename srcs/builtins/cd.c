/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:59:15 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/28 14:39:41 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	actualize_env(t_list **lst)
{
	t_list *tmp;
	char *current_pwd;
	char *oldpwd;

	tmp = *lst;
	current_pwd = NULL;
	oldpwd = NULL;
	while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "PWD"))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(((t_var *)tmp->content)->var, "PWD"))
	{
		current_pwd = getcwd(current_pwd, 0);
		if (((t_var *)tmp->content)->value)
			oldpwd = ft_strdup(((t_var *)tmp->content)->value);
		if (current_pwd)
		{
			free(((t_var *)tmp->content)->value);
			((t_var *)tmp->content)->value = NULL;
			((t_var *)tmp->content)->value = ft_strdup(current_pwd);
		}

	}
	tmp = *lst;
	while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "OLDPWD"))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(((t_var *)tmp->content)->var, "OLDPWD"))
	{
		if (((t_var *)tmp->content)->value)
			free(((t_var *)tmp->content)->value);
		if (oldpwd)
			((t_var *)tmp->content)->value = oldpwd;
	}
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
	if (!arg[1])
	{
		while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "HOME"))
			tmp = tmp->next;
		if (tmp && !ft_strcmp(((t_var *)tmp->content)->var, "HOME"))
			chdir(((t_var *)tmp->content)->value);
		else
		{
			ft_putstr("minishellrose: cd: HOME not set\n"); //ECRIRE SUR LE STDOUT, MAIS BREAK MEME SI PIPE 
			exit(0);
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
				exit(0);
			}
		}
		else
		{
			if (chdir(arg[1]) < 0)
			{
				tcaps.ret = RET_ERROR;
				printf("minishellrose: cd: %s: No such file or directory\n", arg[1]);
				return (0);
			}
		}
	}
	actualize_variables(datas);
	return (0);	
}
