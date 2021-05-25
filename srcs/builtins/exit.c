/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:00:25 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/10 15:43:57 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	string_is_num(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[i]) && (str[i] != '-' && str[i] != '+'))
		return (0);
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int	ft_exit(char **av, t_big *datas)
{
	char	c;

	g_tcaps.ret = 1;
	write(STDOUT_FILENO, "exit\n", 5);
	if (av[1] && !string_is_num(av[1]))
	{
		g_tcaps.ret = 2;
		printi_stderr("exit", ": numeric argument required", 1);
	}
	else if (av[1] && string_is_num(av[1]))
	{
		if (av[2])
		{
			printi_stderr("exit", ": too many arguments", 1);
			return (g_tcaps.ret);
		}
		c = ft_atoi(av[1]);
		g_tcaps.ret = (int)c;
	}
	if (!(update_history_file(datas)))
		g_tcaps.ret = 1;
	free_datas(datas);
	exit(g_tcaps.ret);
	return (g_tcaps.ret);
}
