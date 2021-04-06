/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:14:14 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/02 17:41:01 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	binaires2(int *fd_out)
{
	int fd[2];
	pid_t pid1;

	pipe(fd);
	pid1 = fork();
	dup2(*fd_out, STDIN_FILENO);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		execlp("grep", "grep", "shunting", NULL);
		exit(0);
	}
	waitpid(pid1, NULL, 0);
	dup2(fd[0], *fd_out);
	close(fd[1]);
	close(fd[0]);
}

void	binaires(int *fd_out)
{
	int fd[2];
	pid_t pid1;

	pipe(fd);
	pid1 = fork();
	dup2(*fd_out, STDIN_FILENO);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		execlp("ls", "ls", "-la", NULL);
		exit(0);
	}
	waitpid(pid1, NULL, 0);
	dup2(fd[0], *fd_out);
	close(fd[1]);
	close(fd[0]);
}

int	main(void)
{
	int fd_out;

	fd_out = dup(STDIN_FILENO);
	binaires(&fd_out);
	binaires2(&fd_out);
	char *line;
	while (get_next_line(fd_out, &line))
		printf("%s\n", line);
	close(fd_out);
	return (0);
}
