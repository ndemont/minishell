/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:31:28 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/08 14:44:13 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int			ft_echo_cat(t_node *builtin, int i)
{
	int len;

	while (builtin->arg[i] && builtin->arg[i + 1])
	{
		len = ft_strlen(builtin->arg[i]);
		builtin->ret = (char *)malloc(sizeof(char) * (len + 2));
		if (!builtin->ret)
			print_errors(strerror(errno));
		builtin->ret = strcpy(builtin->ret, builtin->arg[i]);
		builtin->ret[len] = ' ';
		builtin->ret[len + 1] = '\0';
		i++;
	}
	return (1);
}

int			ft_echo_catlast(t_node *builtin, int i, int flag)
{
	int	len;

	len = ft_strlen(builtin->arg[i]);
	builtin->ret = (char *)malloc(sizeof(char) * (len + 1 + flag));
	if (!builtin->ret)
		print_errors(strerror(errno));
	builtin->ret = strcpy(builtin->ret, builtin->arg[i]);
	if (flag)
		builtin->ret[len] = '\n';
	builtin->ret[len + flag] = '\0';
	return (1);
}

int			ft_echo(t_big *datas, t_node *builtin)
{
	int flag;
	int i;

	(void)datas;
	flag = 1;
	if (!builtin->arg[0])
		return (0);
	i = 1;
	if (!(ft_strcmp(builtin->arg[i], "-n")))
	{
		flag = 0;
		i++;
	}
	ft_echo_cat(builtin, i);
	ft_echo_catlast(builtin, i, flag);
	return (1);
}
