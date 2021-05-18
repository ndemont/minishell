/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:10:42 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/18 11:10:43 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_plus_left(char *line)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_split_on_equal(line);
	while (str[0] && str[0][i])
	{
		if (str[0][i] == '+')
		{
			free_double(str);
			return (1);
		}
		i++;
	}
	free_double(str);
	return (0);
}

int		check_arg_conformity(char *line)
{
	int		i;
	char	**str;
	char	*tmp;

	i = 0;
	str = ft_split_on_equal(line);
	if (!str)
	{
		printi_stderr(0, strerror(errno), 0);
		return (BUILT_IN_FAILURE);
	}
	tmp = str[0];
	if (ft_isdigit(tmp[0]) || tmp[0] == 0)
		return (0);
	while (tmp[i])
	{
		if (!ft_isalnum(tmp[i]) && tmp[i] != '_')
		{
			free_double(str);
			return (0);
		}
		i++;
	}
	free_double(str);
	return (1);
}

int		check_plus_conformity(char *line)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_split_on_equal(line);
	while (str[0] && str[0][i])
	{
		if (str[0][i] == '+' && i != (int)(ft_strlen(str[0]) - 1))
		{
			free_double(str);
			return (0);
		}
		i++;
	}
	free_double(str);
	return (1);
}

int		check_duplicate(t_list *list, char *ref)
{
	t_list	*tmp;
	int		count;
	char	*str;
	int		i;

	i = 0;
	while (ref[i] && ref[i] != '=')
		i++;
	str = ft_substr(ref, 0, i);
	tmp = list;
	count = 0;
	while (tmp)
	{
		if (!ft_strcmp(((t_var *)tmp->content)->var, str))
		{
			free(str);
			return (1);
		}
		tmp = tmp->next;
		count++;
	}
	free(str);
	return (0);
}

char	*get_identifier(char *str)
{
	int		i;
	char	*identifier;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[0] == '=')
		identifier = ft_strdup("=");
	else
		identifier = ft_substr(str, 0, i);
	if (!identifier)
		return (printc_stderr(0, strerror(errno), 0));
	return (identifier);
}
