/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:31:28 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/29 18:34:39 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_return_value(void)
{
	char *value;

	value = ft_itoa(tcaps.ret);
	return (value);
}

char		*get_env_var(char *var, t_big *datas)
{
	int		i;
	t_list	*env;
	char	*tmp;
	char	*value;

	tmp = malloc(sizeof(char) * (ft_strlen(var) - 2));
	tmp = ft_substr(var, 2, (ft_strlen(var) - 3));
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
	return (value);
}

char		*ft_echo_cat(char **arg, int *i, t_big *datas)
{
	int		len;
	char	*tmp;
	char	*ret;

	ret = (char *)malloc(sizeof(char));
	ret[0] = 0;
	while (arg[*i] && arg[*i + 1])
	{
		if (arg[*i][0] == '\"' && arg[*i][1] == '$')
			arg[*i] = get_env_var(arg[*i], datas);
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
	return (ret);
}

char 		*ft_echo_catlast(char *ret, char **arg, int *i, int flag, t_big *datas)
{
	int	len;
	char *tmp;

	if (arg[*i][0] == '\"' && arg[*i][1] == '$')
		arg[*i] = get_env_var(arg[*i], datas);
	len = ft_strlen(arg[*i]);
	tmp = ret;
	ret = (char *)malloc(sizeof(char) * (len + ft_strlen(tmp) + 1 + flag));
	if (!ret)
		print_errors(strerror(errno));
	ret = ft_strjoin(tmp, arg[*i]);
	if (flag)
		ret[len + ft_strlen(tmp)] = '\n';
	ret[len + ft_strlen(tmp)+ flag] = '\0';
	free(tmp);
	return (ret);
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
	ret = ft_echo_cat(arg, &i, datas); //PENSER A FREE
	ret = ft_echo_catlast(ret, arg, &i, flag, datas); //NAS, PENSE A FREE STP
	ft_putstr_fd(ret, STDOUT_FILENO);
	tcaps.ret = 0;
	return (1);
}
