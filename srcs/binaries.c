/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:31:47 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/01 13:31:48 by gpetit           ###   ########.fr       */
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

//call this function if (elem->command != 0), Fork higher or here ? 
void	binaries(t_node *token, t_big *datas)
{
	char **cmd;
	int k;
	int pid;
	int status;

	pid = fork();
	cmd = path_array(token->command);
 	k = 0;
	if (pid == 0)
	{
		while (cmd[k] && (execve(cmd[k], token->arg, datas->env) == -1))
			k++;
	}
	else
		wait(&status);
}
