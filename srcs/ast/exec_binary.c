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

char	**path_array(char *command, t_list *env)
{
	char	*tmp;
	char	**paths;
	char	**binaries;
	int		k;

	k = 0;
	paths = NULL;
	while (env && ft_strcmp(((t_var *)(env->content))->var, "PATH"))
		env = env->next;
	if (!env)
	{
		perror("PATH is invalid ");
		exit(0); //replace by custom exit fct that deallocate everything
	}
	if (!ft_strcmp(((t_var *)(env->content))->var, "PATH"))
		paths = ft_split(((t_var *)(env->content))->value, ':');
	if (!paths)
	{
		perror("ft_split failed ");
		exit(0); //replace by custom exit fct that deallocate everything
	}
	tmp = ft_strjoin("/", command);
	binaries = (char **)malloc(sizeof(char *) * (ft_dbstrlen(paths) + 1));
	while (paths[k])
	{
		binaries[k] = ft_strjoin(paths[k], tmp);
		if (!binaries[k])
		{
			printf("k = %i\n", k);
			perror("strjoin_failed");
			exit(0); //replace by custom exit fct that deallocate everything
		}
		k++;
	}
	binaries[k] = 0;
	free(tmp);
	free_double(paths);
	return (binaries);
}

char	**mono_array(char *str)
{
	char **cmd;

	cmd = (char **)malloc(sizeof(char*) * 2);
	if (!cmd)
	{
		perror("Malloc failed in mono_array ");
		exit(0); //replace by custom exit fct
	}
	cmd[0] = ft_strdup(str);
	if (!cmd[0])
	{
		perror("Malloc failed in mono_array2 ");
		exit(0);
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

char	**build_array_env(t_list *lst)
{
	int		size;
	int		i;
	char	*line;
	char	**env;

	i = 0;
	size = ft_lstsize(lst);
	env = (char **)malloc(sizeof(char *) * (size + 1));
	while (lst)
	{
		line = ft_strjoin(((t_var *)(lst->content))->var, "=");
		line = ft_realloc(line, ft_strlen(line) + ft_strlen(((t_var *)(lst->content))->value) + 1);
		ft_strlcat(line, ((t_var *)(lst->content))->value, (ft_strlen(line) + ft_strlen(((t_var *)(lst->content))->value) + 1));
		env[i] = line;
		i++;
		lst = lst->next;
	}
	env[i] = 0;
	return (env);
}

int		exec_binary(char *command, char **argv, t_big *datas)
{
	char	**cmd;
	char	**env;
	int		k;
	int		ret;

	cmd = build_array(command, *datas->env);
	env = build_array_env(*datas->env);
	k = 0;
	while (cmd[k] && ((ret = execve(cmd[k], argv, env)) == -1))
		k++;
	if (ret == -1)
	{
		if (errno == 2)
			tcaps.ret = RET_ERROR;
		else if (errno == 13)
			tcaps.ret = 126;
		ft_putstr_fd("minishellrose: ", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	free_double(cmd);
	free_double(env);
	return (tcaps.ret);
}
