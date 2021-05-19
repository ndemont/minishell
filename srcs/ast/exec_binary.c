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
