/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:31:28 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/08 11:22:53 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int			ft_echo(t_big *datas, t_node *builtin)
{
	int flag;
	int i;
	int len;

	flag = 0;
	if (!builtin->arg[0])
		return (0);
	i = 1;
	if (!(ft_strcmp(builtin->arg[i], "-n")))
	{
		flag = 1;
		i++;
	}
	while (builtin->arg[i] && builtin->arg[i + 1])
	{
		len = ft_strlen(builtin->arg[i]);
		builtin->ret = (char *)malloc(sizeof(char) * (len + 2));
		builtin->ret = strcpy(builtin->ret, builtin->arg[i]);
		builtin->ret[len] = ' ';
		builtin->ret[len] = '\0';
		i++;
	}
	len = ft_strlen(builtin->arg[i]);
	builtin->ret = (char *)malloc(sizeof(char) * (len + 1 + flag));
	builtin->ret = strcpy(builtin->ret, builtin->arg[i]);
	if (flag)
		builtin->ret[len] = '\n';
	builtin->ret[len] = '\0';
	return (1);
}
