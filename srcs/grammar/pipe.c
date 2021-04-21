/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:08:58 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/11 11:02:27 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	actualize_return_status(int ret_status)
{
	tcaps.ret = WEXITSTATUS(ret_status);
}

static void	exec_child(char *command, char *builtin, char **av, t_big *datas)
{
	int		ret_status;
	int		fd[2];
	pid_t	pid1;

	pipe(fd);
	ret_status = 127;
	pid1 = fork();
	tcaps.child = 1;
	if (pid1 == 0)
	{
		dup2(datas->fd, STDIN_FILENO);
		close(datas->fd);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]); //initialement close(fd[1]);
		if (builtin)
			ret_status = exec_built_in(builtin, av, datas);
		else
			exec_binary(command, av, datas);
		free_datas(datas);
		exit(ret_status);
	}
	waitpid(pid1, &ret_status, 0);
	actualize_return_status(ret_status);
	tcaps.child = 0;
	dup2(fd[0], datas->fd);
	close(fd[1]);
	//close(fd[0]); //initialement UNMUTE
}

void		exec_piped_cmd(char *cmd, char *builtin, char **av, t_big *datas)
{
	datas->flag_pipe = 1;
	datas->flag_left_bracket = 0;
	exec_child(cmd, builtin, av, datas);
	if (datas->flag_bracket)
	{
		print_std_fd(datas->fd, datas->fd_out);
		ft_putstr_fd("\n", datas->fd);
		if (datas->fd_out != STDOUT_FILENO)
			close(datas->fd_out);
		datas->fd_out = STDOUT_FILENO;
		datas->flag_pipe = 0;

	}
	datas->flag_bracket = 0;
}
