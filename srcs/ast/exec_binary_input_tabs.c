/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary_input_tabs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 13:51:24 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/19 13:51:34 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_two_elems(char **tmp, char ***paths)
{
	clean_free(tmp);
	free_double(*paths);
}

char	**path_array2(char **tmp, char ***paths)
{
	int		k;
	char	**binaries;

	k = 0;
	binaries = (char **)malloc(sizeof(char *) * (ft_dbstrlen(*paths) + 1));
	if (!(*tmp) || !binaries)
	{
		free_two_elems(tmp, paths);
		return (printcc_stderr(0, strerror(errno), 0));
	}
	while ((*paths)[k])
	{
		binaries[k] = ft_strjoin((*paths)[k], *tmp);
		if (!binaries[k])
		{
			free_two_elems(tmp, paths);
			return (printcc_stderr(0, strerror(errno), 0));
		}
		k++;
	}
	binaries[k] = 0;
	free(*tmp);
	free_double(*paths);
	return (binaries);
}

char	**path_array(char *command, t_list *env)
{
	char	*tmp;
	char	**paths;
	char	**binaries;

	paths = NULL;
	while (env && ft_strcmp(((t_var *)(env->content))->var, "PATH"))
		env = env->next;
	if (!env)
		return (printcc_stderr(0, "PATH is invalid", 1));
	if (!ft_strcmp(((t_var *)(env->content))->var, "PATH"))
		paths = ft_split(((t_var *)(env->content))->value, ':');
	if (!paths)
		return (printcc_stderr(0, strerror(errno), 1));
	tmp = ft_strjoin("/", command);
	binaries = path_array2(&tmp, &paths);
	return (binaries);
}

char	**mono_array(char *str)
{
	char	**cmd;

	cmd = (char **)malloc(sizeof(char *) * 2);
	if (!cmd)
		return (printcc_stderr(0, strerror(errno), 1));
	cmd[0] = ft_strdup(str);
	if (!cmd[0])
	{
		free(cmd);
		return (printcc_stderr(0, strerror(errno), 1));
	}
	cmd[1] = 0;
	return (cmd);
}

char	**build_array(char *command, t_list *env)
{
	char	**cmd;

	if (ft_strchr(command, '/'))
		cmd = mono_array(command);
	else
		cmd = path_array(command, env);
	return (cmd);
}
