/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:08:58 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/19 12:42:14 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	actualize_return_status(int ret_status)
{
	g_tcaps.ret = WEXITSTATUS(ret_status);
}

void	close_pipes(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	pipe_magic(int fd[2], t_big *datas)
{
	int	ret;

	datas->flag_bracket = 0;
	ret = dup2(datas->fd, STDIN_FILENO);
	if (ret == ERR)
	{
		close_pipes(fd);
		free_datas(datas);
		exit(ERR);
	}
	close(datas->fd);
	ret = dup2(fd[1], STDOUT_FILENO);
	if (ret == ERR)
	{
		close_pipes(fd);
		free_datas(datas);
		exit(ERR);
	}
	close_pipes(fd);
}

int	create_pipe_do_fork(int fd[2], pid_t *pid1, int *ret_status)
{
	int	ret;

	ret = pipe(fd);
	if (ret == ERR)
	{
		printi_stderr(0, strerror(errno), 0);
		return (ERR);
	}
	*ret_status = 127;
	*pid1 = fork();
	if (*pid1 == ERR)
	{
		close_pipes(fd);
		printi_stderr(0, strerror(errno), 0);
		return (ERR);
	}
	return (SUCCESS);
}

static int	exec_child(char *command, char *builtin, char **av, t_big *datas)
{
	int		ret;
	int		ret_status;
	int		fd[2];
	pid_t	pid1;

	ret = create_pipe_do_fork(fd, &pid1, &ret_status);
	if (ret == ERR)
		return (ERR);
	if (pid1 == 0)
	{
		pipe_magic(fd, datas);
		if (builtin)
			ret_status = exec_built_in(builtin, av, datas);
		else
			exec_binary(command, av, datas);
		free_datas(datas);
		exit(ret_status);
	}
	happening_in_parents();
	waitpid(pid1, &ret_status, 0);
	actualize_return_status(ret_status);
	dup2(fd[0], datas->fd);
	if (g_tcaps.ret == ERR)
		g_tcaps.exit = 0;
	close_pipes(fd);
	return (SUCCESS);
}

void	exec_piped_cmd(char *cmd, char *builtin, char **av, t_big *datas)
{
	datas->flag_pipe = 1;
	datas->flag_left_bracket = 0;
	g_tcaps.child = 1;
	exec_child(cmd, builtin, av, datas);
	g_tcaps.child = 0;
	if (datas->flag_bracket && g_tcaps.exit)
	{
		print_std_fd(datas->fd, datas->fd_out);
		if (datas->fd_out != STDOUT_FILENO)
			close(datas->fd_out);
		datas->fd_out = STDOUT_FILENO;
		datas->flag_pipe = 0;
	}
	datas->flag_bracket = 0;
}
