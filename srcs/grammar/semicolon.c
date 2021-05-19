/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:04:11 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/19 12:42:10 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(char *command, char **argv, t_big *datas)
{
	pid_t	pid1;
	int		ret_status;

	pid1 = fork();
	g_tcaps.child = 1;
	if (pid1 == 0)
	{
		ret_status = exec_binary(command, argv, datas);
		close(datas->fd);
		free_datas(datas);
		exit(ret_status);
	}
	waitpid(pid1, &ret_status, 0);
	actualize_return_status(ret_status);
	g_tcaps.child = 0;
	if (g_tcaps.ret == ERR)
		g_tcaps.exit = 0;
	close(datas->fd);
}

static int	exec_child2(char *command, char **av, t_big *datas)
{
	int		ret;
	int		ret_status;
	int		fd[2];
	pid_t	pid1;

	ret = create_pipe_do_fork(fd, &pid1, &ret_status);
	if (ret == ERR)
		return (ERR);
	g_tcaps.child = 1;
	if (pid1 == 0)
	{
		g_tcaps.ret = 0;
		pipe_magic(fd, datas);
		exec_binary(command, av, datas);
		free_datas(datas);
		exit(ret_status);
	}
	waitpid(pid1, &ret_status, 0);
	actualize_return_status(ret_status);
	g_tcaps.child = 0;
	dup2(fd[0], datas->fd);
	close_pipes(fd);
	return (SUCCESS);
}

void	exec_semicolon_cmd(char *cmd, char **av, int is_bltn, t_big *datas)
{
	datas->flag_pipe = 0;
	datas->flag_left_bracket = 0;
	if (is_bltn == 1)
		g_tcaps.ret = exec_built_in(cmd, av, datas);
	else if (is_bltn == 2)
	{
		print_std(datas->fd);
		if (datas->fd && datas->fd != STDIN_FILENO && datas->fd != 1)
			close(datas->fd);
		datas->fd = dup(STDIN_FILENO);
	}
	else if (is_bltn == 0 && !datas->flag_bracket && !datas->flag_left_bracket)
		exec_child(cmd, av, datas);
	else if (is_bltn == 0 && (datas->flag_bracket || datas->flag_left_bracket))
		exec_child2(cmd, av, datas);
	if (datas->flag_bracket && g_tcaps.exit)
	{
		print_std_fd(datas->fd, datas->fd_out);
		if (datas->fd_out != STDOUT_FILENO)
			close(datas->fd_out);
		datas->fd_out = STDOUT_FILENO;
	}
	datas->flag_bracket = 0;
}
