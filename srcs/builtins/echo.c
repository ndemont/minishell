/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:31:28 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/03 11:54:34 by ndemont          ###   ########.fr       */
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
	tmp = malloc(sizeof(char) * len);
	tmp = ft_substr(var, *j, len);
	printf("temp = %s\n", tmp);
	if (!ft_strcmp(tmp, "?"))
	{
		value = get_return_value();
		return (value);
	}
	i = 0;
	env = *datas->env;
	value = malloc(sizeof(char));
	value[0] = '\0';
	while (env)
	{
		if (!ft_strcmp(((t_var *)env->content)->var, tmp))
		{
			value = ft_strdup(((t_var *)env->content)->value);
			break ;
		}
		env = env->next;
	}
	*j = *j + len;
	printf("value = %s\n", value);
	return (value);
}

char		*ft_echo_cat(char **arg, int *i, t_big *datas)
{
	char	*tmp1;
	char	*tmp2;
	char	*ret;
	int		j;

	ret = (char *)malloc(sizeof(char));
	ret[0] = 0;
	while (arg[*i] && arg[*i + 1])
	{
		j = 0;
		printf("arg[*i] = [%s]\n", arg[*i]);
		while (arg[*i][j])
		{
			tmp1 = ret;
			if (arg[*i][j] == '\"' && arg[*i][j + 1] == '$')
				tmp2 = get_env_var(arg[*i], &j, datas);
			else
			{
				tmp2 = malloc(sizeof(char) * 2);
				tmp2[0] = arg[*i][j];
				tmp2[1] = 0;
			}
			ret = ft_strjoin(tmp1, tmp2);
			j++;
		}
		ret = ft_strjoin(ret, " ");
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
	ret = (char *)malloc(sizeof(char));
	ret[0] = 0;
	while (arg[*i][j])
	{
		tmp1 = ret;
		if (arg[*i][j] == '\"' && arg[*i][j + 1] == '$')
			tmp2 = get_env_var(arg[*i], &j, datas);
		else
		{
			tmp2 = malloc(sizeof(char) * 2);
			tmp2[0] = arg[*i][j];
			tmp2[1] = 0;
		}
		ret = ft_strjoin(tmp1, tmp2);
		j++;
	}
	printf("arg[*i] = [%s]\n", arg[*i]);
	len = ft_strlen(ret) + ft_strlen(tmp3);
	tmp = ret;
	ret = ft_strjoin(tmp3, tmp);
	if (flag)
		ret = ft_strjoin(ret, "\n");
	free(tmp);
	return (ret);
}

void		ft_add_arg(char **arg, t_big *datas)
{
	int		j;
	int		i;
	int		count;

	count = 0;
	printf("datas->redirection_arg = [%p]\n", datas->redirection_arg);
	printf("datas->redirection_arg = [%p]\n", datas->redirection_arg[0]);
	while (datas->redirection_arg[count])
	{
		printf("copy = [%s]\n", datas->redirection_arg[count]);
		count++;
	}
	i = 0;
	while (arg[i])
		i++;
	count += i;
	arg = (char **)malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (i < count)
	{
		printf("copy = [%s]\n", datas->redirection_arg[j]);
		arg[i] = ft_strdup(datas->redirection_arg[j]);
		i++;
		j++;
	}
	arg[i] = 0;
}

int			ft_echo(char **arg, t_big *datas)
{
	int flag;
	int i;
	char *ret;

	flag = 1;
	i = 1;
	if (!(ft_strcmp(arg[i], "-n")))
	{
		flag = 0;
		i++;
	}
	ft_add_arg(arg, datas);
	ret = ft_echo_cat(arg, &i, datas);
	ret = ft_echo_catlast(ret, arg, &i, flag, datas);
	ft_putstr_fd(ret, datas->fd_out);
	tcaps.ret = 0;
	return (1);
}
