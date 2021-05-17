/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_actualize_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 20:13:19 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/17 20:13:33 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	actualize_pwd(int *pwd_flag, char **oldpwd, t_list *tmp)
{
	char	*current_pwd;

	current_pwd = NULL;
	while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "PWD"))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(((t_var *)tmp->content)->var, "PWD"))
	{
		current_pwd = getcwd(current_pwd, 0);
		if (!current_pwd)
			return (printi_stderr(0, strerror(errno), 0));
		if (((t_var *)tmp->content)->value)
		{
			*pwd_flag = 1;
			*oldpwd = ft_strdup(((t_var *)tmp->content)->value);
		}
		clean_free(&(((t_var *)tmp->content)->value));
		((t_var *)tmp->content)->value = ft_strdup(current_pwd);
	}
	clean_free(&current_pwd);
	if (!(((t_var *)tmp->content)->value) || !(*oldpwd))
	{
		clean_free(oldpwd);
		return (printi_stderr(0, strerror(errno), 0));
	}
	return (SUCCESS);
}

int	actualize_oldpwd(char **oldpwd, t_list *tmp)
{
	while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "OLDPWD"))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(((t_var *)tmp->content)->var, "OLDPWD"))
	{
		clean_free(&(((t_var *)tmp->content)->value));
		if (*oldpwd)
			((t_var *)tmp->content)->value = ft_strdup(*oldpwd);
		if (!((t_var *)tmp->content)->value)
			return (printi_stderr(0, strerror(errno), 0));
	}
	return (SUCCESS);
}

int	cd_actualize_env(t_list **lst)
{
	t_list	*tmp;
	char	*oldpwd;
	int		pwd_flag;
	int		ret;

	oldpwd = NULL;
	pwd_flag = 0;
	tmp = *lst;
	ret = actualize_pwd(&pwd_flag, &oldpwd, tmp);
	if (!ret)
		return (ERROR);
	if (pwd_flag)
	{
		tmp = *lst;
		ret = actualize_oldpwd(&oldpwd, tmp);
		if (!ret)
		{
			clean_free(&oldpwd);
			return (ERROR);
		}
	}
	clean_free(&oldpwd);
	return (SUCCESS);
}
