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

int	main(int ac, char **av, char **env)
{
	char *cmd;
	pid_t pid;
	pid_t pid2;
	int fd[2];
	

	(void)ac;
	if ((pipe(fd) == -1))
	{
		perror("Pipe not Working ");
		exit(0);
	}
	if ((pid = fork()) == -1)
	{
		perror("pid error ");
		exit(0);
	}
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "shunting", "shunting_yard.c" NULL);
		free(cmd);
		exit(0);
	}
	if ((pid2 = fork()) == -1)
	{
		perror("pid error ");
		exit(0);
	}
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		char *line;
		get_next_line(STDIN_FILENO, &line);
		printf("line = %s\n", line);
		execlp("grep", "grep", "shunting", NULL);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
