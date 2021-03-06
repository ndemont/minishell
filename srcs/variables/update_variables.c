/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 11:27:25 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/25 15:03:50 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cat_var(char *str, int *i, t_big *datas, int *start)
{
	char	*var;

	if (str[*i] == '\"' && str[*i + 1] == '$')
	{
		var = get_env_var(str, i, datas);
		if (!(var))
			return (0);
		*i = *i + 1;
		*start = *i;
	}
	else
	{
		while (str[*i] && (str[*i] != '\"' || str[*i + 1] != '$'))
			*i = *i + 1;
		var = ft_substr(str, *start, *i - *start);
		if (!(var))
			return (printc_stderr(0, strerror(errno), 0));
	}
	return (var);
}

static char	*get_str(char *str, t_big *datas, int *i)
{
	int		start;
	char	*var;
	char	*new;
	char	*tmp;

	start = *i;
	new = malloc(sizeof(char));
	new[0] = 0;
	while (str[*i])
	{
		var = cat_var(str, i, datas, &start);
		if (!var)
			return (0);
		tmp = new;
		new = ft_strjoin(new, var);
		clean_free(&tmp);
		clean_free(&var);
		if (!new)
			return (printc_stderr(0, strerror(errno), 0));
	}
	return (new);
}

char	*join_variable(char *tmp, char *var, char *new)
{
	if (tmp)
	{
		new = ft_strjoin(tmp, var);
		if (!(new))
		{
			clean_free(&var);
			clean_free(&tmp);
			return (printc_stderr(0, strerror(errno), 0));
		}
		clean_free(&var);
		clean_free(&tmp);
	}
	else
		new = var;
	return (new);
}

char	*check_variable(char *str, t_big *datas)
{
	int		i;
	char	*var;
	char	*new;
	char	*tmp;

	i = 0;
	new = malloc(sizeof(char));
	if (!new)
		return (printc_stderr(0, strerror(errno), 0));
	new[0] = 0;
	while (str[i])
	{
		tmp = new;
		var = get_str(str, datas, &i);
		if (!(var))
		{
			clean_free(&new);
			return (0);
		}
		new = join_variable(tmp, var, new);
		if (!new)
			return (0);
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
		if (!root->arg[i])
			return (0);
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
