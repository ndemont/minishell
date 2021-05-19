/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 23:42:51 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/19 14:03:37 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_built_in(char *command, char **argv, t_big *datas)
{
	int	ret;

	if (datas->flag_bracket)
	{
		exec_piped_cmd(NULL, command, argv, datas);
		return (1);
	}
	if (!(ft_strcmp(command, "echo")))
		ret = ft_echo(argv, datas);
	if (!(ft_strcmp(command, "cd")))
		ret = ft_cd(argv, datas);
	if (!(ft_strcmp(command, "env")))
		ret = ft_env(argv, datas);
	if (!(ft_strcmp(command, "pwd")))
		ret = ft_pwd(datas);
	if (!(ft_strcmp(command, "export")))
		ret = ft_export(argv, datas);
	if (!(ft_strcmp(command, "unset")))
		ret = ft_unset(argv, datas);
	if (!(ft_strcmp(command, "exit")))
		ret = ft_exit(argv, datas);
	if (ft_strchr(command, '='))
		ret = ft_hidden(argv, datas);
	return (ret);
}
