/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:04:11 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/27 21:41:19 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_semicolon_cmd(char *command, char **argv, int is_built_in, t_big *datas)
{
	int		fd[2];
	pid_t	pid1;

	datas->flag_pipe = 0;
	if (datas->flag_bracket)
		ft_putstr_fd(datas->redirection_arg, datas->fd);
	datas->flag_bracket = 0;
	datas->flag_left_bracket = 0;
	if (is_built_in == 1)
		exec_built_in(command, argv, datas);
	else if (is_built_in == 2)
		print_std(datas->fd);
	else if (is_built_in == 0)
	{
		pipe(fd);
		pid1 = fork();
		if (pid1 == 0)
		{
			dup2(datas->fd, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
			exec_binary(command, argv);
			close(datas->fd);
			exit(0);
		}
		waitpid(pid1, NULL, 0);
		dup2(fd[0], datas->fd);
		close(fd[1]);
		close(fd[0]);
	}
}
