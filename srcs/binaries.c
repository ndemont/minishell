/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:31:47 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/02 12:39:24 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **path_array(char *command)
{
	char *tmp;
	char **paths;
	char **binaries;
	int k;

	k = 0;
	if ((tmp = getenv("PATH")) == NULL)
	{
		perror("PATH is invalid ");
		exit(0); //replace by custom exit fct that deallocate everything 
	}
	paths = ft_split(tmp, ':');
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
			exit (0); //replace by custom exit fct that deallocate everything 
		}
		k++;
	}
	binaries[k] = 0;
	free(tmp);
	free_double(paths);
	return (binaries);
}

char **mono_array(char *str)
{
	char **cmd;

	cmd = (char **)malloc(sizeof(char*) * 1);
	if (!cmd)
	{
		perror("Malloc failed in mono_array ");
		exit(0); //replace by custom exit fct
	}
	cmd[0] = ft_strdup(str);
	if (!cmd[0])
	{
		perror("Malloc failed in mono_array2 ");
		exit (0);
	}
	cmd[1] = 0;
	return (cmd);
}

//call this function if (elem->command != 0), Fork higher or here ? 
void	binaries(t_node *token, t_big *datas)
{
	char **cmd;
	int k;
	int pid;
	int ret;
	int status;

	pid = fork();
	if (ft_strchr(token->command, '/'))
		cmd = mono_array(token->command);
	else
		cmd = path_array(token->command);
 	k = 0;
	if (pid == 0)
	{
		while (cmd[k] && ((ret = execve(cmd[k], token->arg, datas->env)) == -1))
			k++;
		if (ret == -1)
		{
			write(1, "minishellrose: ", 15);
			ft_putstr(token->command);
			write(1, ": command not found\n", 20);
		}
		exit(0); //permet de fermer execve dans le fork après l'avoir RUN
	}
	else
		wait(&status);
}
