/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 23:41:58 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/17 23:47:02 by ndemont          ###   ########.fr       */
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

char	*env_line(t_list *lst, char ***env)
{
	char	*line;
	int		size;

	line = ft_strjoin(((t_var *)(lst->content))->var, "=");
	if (!line)
	{
		free_double(*env);
		printi_stderr(0, strerror(errno), 0);
		return (ERROR);
	}
	size = ft_strlen(line) + ft_strlen(((t_var *)(lst->content))->value) + 1;
	line = ft_realloc(line, size);
	if (!line)
	{
		free_double(*env);
		printi_stderr(0, strerror(errno), 0);
		return (ERROR);
	}
	ft_strlcat(line, ((t_var *)(lst->content))->value, size);
	return (line);
}

char	**build_array_env(t_list *lst)
{
	int		size;
	int		i;
	char	*line;
	char	**env;

	i = 0;
	size = ft_lstsize(lst);
	env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env)
		return (printcc_stderr(0, strerror(errno), 0));
	while (lst)
	{
		line = env_line(lst, &env);
		if (!line)
			return (ERROR);
		env[i] = line;
		i++;
		lst = lst->next;
	}
	env[i] = 0;
	return (env);
}

int	exec_binary(char *command, char **argv, t_big *datas)
{
	char	**cmd;
	char	**env;
	int		k;
	int		ret;

	cmd = build_array(command, *datas->env);
	env = build_array_env(*datas->env);
	if (!cmd || !env)
		return (ERR);
	k = 0;
	ret = execve(cmd[k], argv, env);
	while (cmd[k] && ret == -1)
		ret = execve(cmd[++k], argv, env);
	if (ret == -1)
	{
		if (errno == 2)
			tcaps.ret = RET_ERROR;
		else if (errno == 13)
			tcaps.ret = 126;
		printi_stderr(argv[0], ": command not found\n", 1);
	}
	free_double(cmd);
	free_double(env);
	return (tcaps.ret);
}
