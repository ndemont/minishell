/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:31:28 by ndemont           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/04/08 17:45:51 by ndemont          ###   ########.fr       */
=======
/*   Updated: 2021/04/08 14:44:13 by ndemont          ###   ########.fr       */
>>>>>>> bec5a084cbcce4052da667fa13b8aed596037b98
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

char		*ft_echo_cat(char **arg, int *i)
{
	int		len;
	char	*tmp;
	char	*ret;

	ret = (char *)malloc(sizeof(char));
	ret[0] = 0;
	while (arg[*i] && arg[*i + 1])
	{
		len = ft_strlen(arg[*i]);
		tmp = ret;
		ret = (char *)malloc(sizeof(char) * (len + 2 + ft_strlen(tmp)));
		if (!ret)
			print_errors(strerror(errno));
		ret = ft_strjoin(tmp, arg[*i]);
		ret[len + ft_strlen(tmp)] = ' ';
		ret[len + 1 + ft_strlen(tmp)] = '\0';
		*i = *i + 1;
		free(tmp);
	}
<<<<<<< HEAD
	return (ret);
=======
	return (1);
>>>>>>> bec5a084cbcce4052da667fa13b8aed596037b98
}

char 		*ft_echo_catlast(char *ret, char **arg, int *i, int flag)
{
	int	len;
	char *tmp;

	len = ft_strlen(arg[*i]);
	tmp = ret;
	ret = (char *)malloc(sizeof(char) * (len + ft_strlen(tmp) + 1 + flag));
	if (!ret)
		print_errors(strerror(errno));
	ret = ft_strjoin(tmp, arg[*i]);
	if (flag)
<<<<<<< HEAD
		ret[len + ft_strlen(tmp)] = '\n';
	ret[len + ft_strlen(tmp)+ flag] = '\0';
	free(tmp);
	return (ret);
=======
		builtin->ret[len] = '\n';
	builtin->ret[len + flag] = '\0';
	return (1);
>>>>>>> bec5a084cbcce4052da667fa13b8aed596037b98
}

int			ft_echo(char **arg)
{
	int flag;
	int i;
<<<<<<< HEAD
	char *ret;
=======
>>>>>>> bec5a084cbcce4052da667fa13b8aed596037b98

	(void)datas;
	flag = 1;
	i = 1;
	if (!(ft_strcmp(arg[i], "-n")))
	{
		flag = 0;
		i++;
	}
	ret = ft_echo_cat(arg, &i); //PENSER A FREE
	ret = ft_echo_catlast(ret, arg, &i, flag); //NAS, PENSE A FREE STP
	//printf("ret 2 = [%s]\n", ret);
	ft_putstr_fd(ret, STDOUT_FILENO);
	return (1);
}
