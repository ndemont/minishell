/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:08:58 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/03 15:43:39 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
void	actualize_return_status(int ret_status)
{
	tcaps.ret = WEXITSTATUS(ret_status);
}

static void	exec_child(char *command, char **av, int is_built_in, t_big *datas)
=======
static void	exec_child(char *cmd, char *builtin, char **av, t_big *datas)
>>>>>>> daed4fa (no prb with normal commands)
{
	int		ret_status;
	int		fd[2];
	pid_t	pid1;

	pipe(fd);
	pid1 = fork();
	tcaps.child = 1;
	if (pid1 == 0)
	{
		dup2(datas->fd, STDIN_FILENO);
		close(datas->fd);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (builtin)
			exec_built_in(builtin, av, datas);
		else
			exec_binary(cmd, av);
		exit(0);
	}
	waitpid(pid1, &ret_status, 0);
	actualize_return_status(ret_status);
	tcaps.child = 0;
	dup2(fd[0], datas->fd);
	close(fd[1]);
	close(fd[0]);
}

void		exec_piped_cmd(char *cmd, char *builtin, char **av, t_big *datas)
{
	datas->flag_pipe = 1;
	datas->flag_bracket = 0;
	datas->flag_left_bracket = 0;
	exec_child(cmd, builtin, av, datas);
	datas->fd_out = STDOUT_FILENO;
}
