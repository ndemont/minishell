/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:27:25 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/16 20:06:22 by ndemont          ###   ########.fr       */
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

char		*get_env_var(char *str, int *i, t_big *datas)
{
	t_list	*env;
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
	env = *datas->env;
	while (env)
	{
		if (!ft_strcmp(((t_var *)env->content)->var, var))
		{
			free(value);
			if (!(value = ft_strdup(((t_var *)env->content)->value)))
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

char	*check_variable(char *str, t_big *datas)
{
	int		i;
	int		start;
	char	*var;
	char	*new;
	char	*tmp;

	i = 0;
	start = 0;
	new = 0;
	while (str[i])
	{
		tmp = new;
		if (str[i] == '\"' && str[i + 1] == '$')
		{
			if (!(var = get_env_var(str, &i, datas)))
			{
				free(new);
				return (0);
			}
			i++;
		}
		else
		{
			while (str[i] && str[i] != '\"')
				i++;
			if (!(var = ft_substr(str, start, i - start)))
			{
				free(new);
				return (printc_stderr(0, strerror(errno), 0));
			}
		}
		if (tmp)
		{
			if (!(new = ft_strjoin(tmp, var)))
			{
				free(var);
				free(tmp);
				return (printc_stderr(0, strerror(errno), 0));
			}
			free(tmp);
			free(var);
		}
		else
			new = var;
		start = i;
	}
	return (new);
}

char	**replace_variable(t_node *root, t_big *datas)
{
	int		i;
	char	*tmp;

	i = 0;
	while (root->arg && root->arg[i])
	{
		tmp = root->arg[i];
		root->arg[i] = check_variable(root->arg[i], datas);
		free(tmp);
		i++;
	}
	if (root->command)
	{
		free(root->command);
		root->command = ft_strdup(root->arg[0]);
	}
	else if (root->builtin)
	{
		free(root->builtin);
		root->builtin = ft_strdup(root->arg[0]);
	}
	return (root->arg);
}
