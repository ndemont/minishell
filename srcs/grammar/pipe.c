/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:08:58 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/21 12:19:43 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_piped_cmd(char *command, char **argv, int is_built_in, t_big *datas)
{
	int fd[2];
	pid_t pid1;

	datas->flag_pipe = 1;
	datas->flag_bracket = 0;
	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(datas->fd, STDIN_FILENO);
		close(datas->fd);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		if (is_built_in == 1)
			exec_built_in(command, argv, datas);
		else
			exec_binary(command, argv);
		exit(0);  //permet de fermer execve dans le fork après l'avoir RUN
	}
	waitpid(pid1, NULL, 0);
	dup2(fd[0], datas->fd);
	close(fd[1]);
	close(fd[0]);
}
