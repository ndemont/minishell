/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:59:15 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/09 20:13:13 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	actualize_env(char **oldpath, t_big *datas)
{
	t_list *tmp;
	char *pwd;

	tmp = *datas->env;
	pwd = NULL;
	while (tmp)
	{
		if (!ft_strcmp(((t_var *)tmp->content)->var, "OLDPWD"))
		{
			free(((t_var *)tmp->content)->value);
			((t_var *)tmp->content)->value = ft_strdup(*oldpath);
		}
		if (!ft_strcmp(((t_var *)tmp->content)->var, "PWD"))
		{
			pwd = getcwd(pwd, 0);
			free(((t_var *)tmp->content)->value);
			((t_var *)tmp->content)->value = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	free(*oldpath);
	free(pwd);
}

int		ft_cd(char **arg, t_big *datas)
{
	t_list *tmp;
	char *oldpath;
	char *newlocation;

	newlocation = NULL;
	oldpath = getcwd(NULL, 0);
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
				ft_putstr((newlocation = getcwd(NULL, 0)));
				ft_putchar('\n');
			}
			else
			{
				ft_putstr("minishellrose: cd: OLDPWD not set\n"); //ECRIRE SUR LE STDOUT, MAIS BREAK MEME SI PIPE 
				exit(0);
			}
		}
		else
			chdir(arg[1]);
	}
	actualize_env(&oldpath, datas);
	if (newlocation)
		free(newlocation);
	return (0);	
}
