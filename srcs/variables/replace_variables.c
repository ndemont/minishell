/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 10:38:53 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/25 12:32:00 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_str_var(char *str, int *i)
{
	int		len;
	char	*var;

	*i = *i + 2;
	len = 0;
	while (str[*i + len] && str[*i + len] != '\"')
		len++;
	var = ft_substr(str, *i, len);
	if (!(var))
		return (printc_stderr(0, strerror(errno), 0));
	*i = *i + len;
	return (var);
}

char	*find_var(t_big *datas, char *str, int *i)
{
	t_list	*env;
	char	*value;
	char	*var;
	char	*tmp;

	env = *datas->env;
	value = ft_strdup("");
	var = get_str_var(str, i);
	if (!(var))
		return (0);
	while (env)
	{
		if (!ft_strcmp(((t_var *)env->content)->var, var))
		{
			tmp = value;
			value = ft_strdup(((t_var *)env->content)->value);
			clean_free(&tmp);
			break ;
		}
		env = env->next;
	}
	clean_free(&var);
	if (!(value))
		return (printc_stderr(0, strerror(errno), 0));
	return (value);
}

char	*get_env_var(char *str, int *i, t_big *datas)
{
	char	*value;

	if (str[*i + 2] == '?')
	{
		value = ft_strdup("\"$?\"");
		(*i) += 3;
		if (!value)
			printc_stderr(0, strerror(errno), 0);
	}
	else
		value = find_var(datas, str, i);
	return (value);
}
