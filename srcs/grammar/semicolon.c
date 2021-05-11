/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:04:11 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/11 11:20:35 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(char *command, char **argv, t_big *datas)
{
	pid_t	pid1;
	int		ret_status;

	pid1 = fork();
	if (pid1 == 0)
	{
		exec_binary(command, argv, datas);
		close(datas->fd);
		free_datas(datas);
		exit(0);
	}
	waitpid(pid1, &ret_status, 0);
	actualize_return_status(ret_status);
	close(datas->fd);
}

void		exec_semicolon_cmd(char *cmd, char **av, int is_builtin, t_big *datas)
{
	datas->flag_pipe = 0;
	if (datas->flag_bracket && datas->redirection_arg)
		ft_putstr_fd(*datas->redirection_arg, datas->fd);
	datas->flag_bracket = 0;
	datas->flag_left_bracket = 0;
	if (is_builtin == 1)
		exec_built_in(cmd, av, datas);
	else if (is_builtin == 2)
		print_std(datas->fd);
	else if (is_builtin == 0)
		exec_child(cmd, av, datas);
}
