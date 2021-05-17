/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 10:38:53 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/17 15:45:27 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_return_value(void)
{
	char *value;

	value = ft_itoa(tcaps.ret);
	return (value);
}

char		*get_str_var(char *str, int *i)
{
	int		len;
	char	*var;

	*i = *i + 2;
	len = 0;
	while (str[*i + len] && str[*i + len] != '\"')
		len++;
	if (!(var = ft_substr(str, *i, len)))
		return (printc_stderr(0, strerror(errno), 0));
	*i = *i + len;
	return (var);
}

char		*init_value(char *var)
{
	char *value;

	if (!(value = malloc(sizeof(char))))
	{
		free(var);
		return (printc_stderr(0, strerror(errno), 0));
	}
	value[0] = '\0';
	return (value);
}

char		*find_var(char *var, char *value, t_big *datas)
{
	t_list	*env;

	env = *datas->env;
	while (env)
	{
		if (!ft_strcmp(((t_var *)env->content)->var, var))
		{
			free(value);
			value = ft_strdup(((t_var *)env->content)->value);
			if (!(value))
			{
				free(var);
				return (printc_stderr(0, strerror(errno), 0));
			}
			break ;
		}
		env = env->next;
	}
	free(var);
	return (value);
}

char		*get_env_var(char *str, int *i, t_big *datas)
{
	int		start;
	char	*var;
	char	*value;

	if (str[*i + 2] == '?')
	{
		value = get_return_value();
		*i = *i + 3;
		start = *i;
		while (str[*i] && str[*i] != '\"')
			*i = *i + 1;
		var = ft_substr(str, start, *i - start);
		if (var)
			value = ft_strjoin(value, var);
		return (value);
	}
	if (!(var = get_str_var(str, i)))
		return (0);
	if (!(value = init_value(var)))
		return (0);
	value = find_var(var, value, datas);
	return (value);
}
