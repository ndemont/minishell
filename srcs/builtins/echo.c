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

char		*ft_echo_cat(char **arg, int i)
{
	int len;
	char *ret;

	while (arg[i] && arg[i + 1])
	{
		len = ft_strlen(arg[i]);
		ret = (char *)malloc(sizeof(char) * (len + 2));
		if (!ret)
			print_errors(strerror(errno));
		ret = strcpy(ret, arg[i]);
		ret[len] = ' ';
		ret[len + 1] = '\0';
		i++;
	}
	return (ret);
}

char 		*ft_echo_catlast(char *ret, char **arg, int i, int flag)
{
	int	len;
	char *tmp;

	len = ft_strlen(arg[i]);
	tmp = (char *)malloc(sizeof(char) * (len + 1 + flag));
	if (!tmp)
		print_errors(strerror(errno));
	tmp = strcpy(ret, arg[i]);
	if (flag)
		tmp[len] = '\n';
	tmp[len + flag] = '\0';
	return (tmp);
}

int			ft_echo(char **arg)
{
	int flag;
	int i;
	char *ret;

	(void)datas;
	flag = 1;
	if (!arg[0])
		return (0);
	i = 1;
	if (!(ft_strcmp(arg[i], "-n")))
	{
		flag = 0;
		i++;
	}
	ret = ft_echo_cat(arg, i); //PENSER A FREE
	ret = ft_echo_catlast(ret, arg, i, flag); //NAS, PENSE A FREE STP
	ft_putstr_fd(ret, STDOUT_FILENO);
	return (1);
}
