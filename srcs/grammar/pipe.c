/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:08:58 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/28 12:49:58 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_piped_cmd(char *command, char **av, int is_built_in, t_big *datas)
{
	int		fd[2];
	pid_t	pid1;

	write(1, "0\n", 2);
	datas->flag_pipe = 1;
	if (datas->flag_bracket)
		ft_putstr_fd(datas->redirection_arg, datas->fd);
	datas->flag_bracket = 0;
	datas->flag_left_bracket = 0;
	pipe(fd);
	pid1 = fork();
	tcaps.child = 1;
	if (pid1 == 0)
	{
		dup2(datas->fd, STDIN_FILENO);
		close(datas->fd);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (is_built_in == 1)
			exec_built_in(command, av, datas);
		else
			exec_binary(command, av);
		exit(0);
	}
	waitpid(pid1, NULL, 0);
	tcaps.child = 0;
	dup2(fd[0], datas->fd);
	close(fd[1]);
	close(fd[0]);
}
