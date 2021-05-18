/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:31:28 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/18 18:01:31 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_add_space(char **arg, char *ret, int *i)
{
	char *tmp;

	if (arg[*i + 1])
	{
		tmp = ret;
		if (!(ret = ft_strjoin(ret, " ")))
		{
			clean_free(&tmp);
			return (printc_stderr(0, strerror(errno), 0));
		}
		clean_free(&tmp);
	}
	return (ret);
}

char		*ft_echo_cat(char **arg, int *i)
{
	char	*tmp;
	char	*ret;
	int		j;

	ret = (char *)malloc(sizeof(char));
	if (!(ret))
		return (printc_stderr(0, strerror(errno), 0));
	ret[0] = 0;
	while (arg[*i])
	{
		j = 0;
		tmp = ret;
		ret = ft_strjoin(ret, arg[*i]);
		if (!ret)
		{
			clean_free(&tmp);
			return (printc_stderr(0, strerror(errno), 0));
		}
		clean_free(&tmp);
		ret = ft_add_space(arg, ret, i);
		if (!ret)
			return (0);
		*i = *i + 1;
	}
	return (ret);
}

int			check_echo_flag(char *str)
{
	int i;

	i = 0;
	if (!ft_strcmp(str, "-n"))
		return (1);
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

char		*ft_echo_option(int flag, char *ret)
{
	char *tmp;

	if (flag)
	{
		tmp = ret;
		if (!(ret = ft_strjoin(ret, "\n")))
		{
			free(tmp);
			return (0);
		}
		free(tmp);
	}
	return (ret);
}

int			ft_echo(char **arg, t_big *datas)
{
	int		i;
	int		flag;
	char	*ret;

	(void)datas;
	flag = 1;
	i = 1;
	while (arg[i] && check_echo_flag(arg[i]))
	{
		flag = 0;
		i++;
	}
	if (!(ret = ft_echo_cat(arg, &i)))
		return (0);
	if (!(ret = ft_echo_option(flag, ret)))
		return (0);
	ft_putstr_fd(ret, STDOUT_FILENO);
	if (ret)
		free(ret);
	tcaps.ret = 0;
	return (tcaps.ret);
}
