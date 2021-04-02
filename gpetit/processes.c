/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:14:14 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/01 10:47:33 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char *cmd;
	int pid;
	int	status;
	char *path;
	char **paths;

	(void)ac;
	pid = fork();
	if (pid == 0)
	{
		while (paths[k])
		{
			cmd = ft_strjoin(paths[k], tmp);
			printf("cmd =  %s\n", cmd);
			printf("retour de EXECVE = %i\n", execve(cmd, av + 1, env));
			free(cmd);
			printf("k = %i\n", k);
			k++;
		}
		free(tmp);
		printf("errno = %i\n", errno);
		perror(NULL);
	}
	else
	{
		wait(&status);
	}
	return (0);
}
