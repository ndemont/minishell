/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:31:28 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/11 15:54:45 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_return_value(void)
{
	char *value;

	value = ft_itoa(tcaps.ret);
	return (value);
}

char		*get_env_var(char *var, int *j, t_big *datas)
{
	int		i;
	int		len;
	t_list	*env;
	char	*tmp;
	char	*value;

	*j = *j + 2;
	len = 0;
	while (var[*j + len] && var[*j + len] != '\"')
		len++;
	if (!(tmp = ft_substr(var, *j, len)))
		return (0);
	if (!ft_strcmp(tmp, "?"))
	{
		*j = *j + 1;
		free(tmp);
		return (get_return_value());
	}
	i = 0;
	env = *datas->env;
	if (!(value = malloc(sizeof(char))))
	{
		free(tmp);
		return (0);
	}
	value[0] = '\0';
	while (env)
	{
		if (!ft_strcmp(((t_var *)env->content)->var, tmp))
		{
			free(value);
			value = ft_strdup(((t_var *)env->content)->value);
			break ;
		}
		env = env->next;
	}
	free(tmp);
	*j = *j + len;
	return (value);
}

char		*ft_echo_cat(char **arg, int *i, t_big *datas)
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
			if (arg[*i][j] == '\"' && arg[*i][j + 1] == '$')
			{
				if (!(tmp2 = get_env_var(arg[*i], &j, datas)))
				{
					free(tmp1);
					return (0);
				}
			}
			else
			{
				if (!(tmp2 = malloc(sizeof(char) * 2)))
				{
					free(tmp1);
					return (0);
				}
				tmp2[0] = arg[*i][j];
				tmp2[1] = 0;
			}
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

char 		*ft_echo_catlast(char *ret, char **arg, int *i, int flag, t_big *datas)
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
		if (arg[*i][j] == '\"' && arg[*i][j + 1] == '$')
		{
			if (!(tmp2 = get_env_var(arg[*i], &j, datas)))
			{
				free(tmp3);
				free(tmp1);
				return (0);
			}
		}
		else
		{
			if (!(tmp2 = malloc(sizeof(char) * 2)))
			{
				free(tmp3);
				free(tmp1);
				return (0);
			}
			tmp2[0] = arg[*i][j];
			tmp2[1] = 0;
		}
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

char		**ft_add_arg(char **arg, t_big *datas)
{
	int		j;
	int		i;
	int		count;
	char	**tmp;

	count = 0;
	while (datas->redirection_arg[count])
		count++;
	i = 0;
	while (arg[i])
		i++;
	count += i;
	tmp = arg;
	if (!(arg = (char **)malloc(sizeof(char *) * (count + 1))))
		return (0);
	arg[count] = 0;
	j = 0;
	while (tmp[j])
	{
		arg[j] = tmp[j];
		j++;
	}
	if (tmp)
		free(tmp);
	j = 0;
	while (i < count)
	{
		if (!(arg[i] = ft_strdup(datas->redirection_arg[j])))
			return (0);
		i++;
		j++;
	}
	return (arg);
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
	if (datas->redirection_arg)
	{
		if (!(arg = ft_add_arg(arg, datas)))
			return (0);
		datas->redirection_arg = 0;
	}
	if (!(ret = ft_echo_cat(arg, &i, datas)))
		return (0);
	if (!(ret = ft_echo_catlast(ret, arg, &i, flag, datas)))
		return (0);
	ft_putstr_fd(ret, STDOUT_FILENO);
	if (ret)
		free(ret);
	tcaps.ret = 0;
	return (tcaps.ret);
}
