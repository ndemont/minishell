/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:20:32 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/20 12:20:39 by gpetit           ###   ########.fr       */
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
