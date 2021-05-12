/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:31:28 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/12 13:48:15 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_return_value(void)
{
	char *value;

	value = ft_itoa(tcaps.ret);
	return (value);
}

char		*ft_echo_cat(char **arg, int *i)
{
	char	*tmp1;
	char	*tmp2;
	char	*ret;
	int		j;

	if (!(ret = (char *)malloc(sizeof(char))))
		return (0);
	ret[0] = 0;
	while (arg[*i] && arg[*i + 1])
	{
		j = 0;
		while (arg[*i][j])
		{
			tmp1 = ret;
			if (!(tmp2 = malloc(sizeof(char) * 2)))
			{
				free(tmp1);
				return (0);
			}
			tmp2[0] = arg[*i][j];
			tmp2[1] = 0;
			if (!(ret = ft_strjoin(tmp1, tmp2)))
			{
				free(tmp1);
				free(tmp2);
				return (0);
			}
			free(tmp1);
			free(tmp2);
			j++;
		}
		tmp1 = ret;
		if (!(ret = ft_strjoin(ret, " ")))
		{
			free(tmp1);
			return (0);
		}
		free(tmp1);
		*i = *i + 1;
	}
	return (ret);
}

char 		*ft_echo_catlast(char *ret, char **arg, int *i, int flag)
{
	int		j;
	int		len;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp3 = ret;
	j = 0;
	if (!(ret = (char *)malloc(sizeof(char))))
		return (0);
	ret[0] = 0;
	while (arg[*i] && arg[*i][j])
	{
		tmp1 = ret;
		if (!(tmp2 = malloc(sizeof(char) * 2)))
		{
			free(tmp3);
			free(tmp1);
			return (0);
		}
		tmp2[0] = arg[*i][j];
		tmp2[1] = 0;
		if (!(ret = ft_strjoin(tmp1, tmp2)))
		{
			free(tmp1);
			free(tmp2);
			free(tmp3);
			return (0);
		}
		free(tmp1);
		free(tmp2);
		j++;
	}
	len = ft_strlen(ret) + ft_strlen(tmp3);
	tmp = ret;
	if (!(ret = ft_strjoin(tmp3, tmp)))
	{
		free(tmp);
		free(tmp3);
		return (0);
	}
	free(tmp);
	free(tmp3);
	if (flag)
	{
		tmp = ret;
		if (!(ret = ft_strjoin(ret, "\n")))
		{
			free(tmp);
			return(0);
		}
		free(tmp);
	}
	return (ret);
}

int			check_echo_flag(char *str)
{
	int i;

	i = 0;
	if (!ft_strcmp(str, "-n"))
		return(1);
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

int			ft_echo(char **arg, t_big *datas)
{
	int flag;
	int i;
	char *ret;

	flag = 1;
	i = 1;
	while (arg[i] && check_echo_flag(arg[i]))
	{
		flag = 0;
		i++;
	}
	arg = get_arguments(arg, arg[0], datas);
	replace_variable(arg, arg[0], datas);
	if (!(ret = ft_echo_cat(arg, &i)))
		return (0);
	if (!(ret = ft_echo_catlast(ret, arg, &i, flag)))
		return (0);
	ft_putstr_fd(ret, STDOUT_FILENO);
	if (ret)
		free(ret);
	tcaps.ret = 0;
	return (tcaps.ret);
}
