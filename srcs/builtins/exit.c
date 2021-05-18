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

int	ft_exit(char **av, t_big *datas)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (av && *av && av[1])
	{
		tcaps.ret = 1;
		printf("minishellrose: exit: %s: numeric argument required\n", av[1]);
	}
	free_datas(datas);
	exit(1);
	return (tcaps.ret);
}
