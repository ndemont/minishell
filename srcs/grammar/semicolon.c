/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:04:11 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/02 19:34:40 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(char *command, char **argv, t_big *datas)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == 0)
	{
		exec_binary(command, argv);
		close(datas->fd);
		exit(0);
	}
	waitpid(pid1, NULL, 0);
	close(datas->fd);
}

void		exec_semicolon_cmd(char *cmd, char **av, int is_builtin, t_big *datas)
{
	datas->flag_pipe = 0;
	if (datas->flag_bracket)
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
