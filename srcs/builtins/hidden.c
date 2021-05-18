/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:36:01 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/06 11:33:53 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_on_equal(char *str)
{
	int		i;
	char	**arg;

	i = 0;
	arg = (char **)malloc(sizeof(char *) * 3);
	if (!arg)
		return (printcc_stderr(0, strerror(errno), 0));
	while (str[i] && str[i] != '=')
		i++;
	arg[0] = ft_substr(str, 0, i);
	if (!arg[0])
	{
		free_double(arg);
		return (printcc_stderr(0, strerror(errno), 0));
	}
	if (str[i] == '=')
		i++;
	arg[1] = ft_substr(str, i, ft_strlen(str) - i);
	if (!arg[1])
	{
		free_double(arg);
		return (printcc_stderr(0, strerror(errno), 0));
	}
	arg[2] = 0;
	return (arg);
}

int	add_to_list(char *line, t_list **list)
{
	t_list	*new;
	t_var	*content;

	content = fill_tmp(line);
	if (!content)
		return (ERROR);
	new = ft_lstnew(content);
	if (!new)
		return (ERROR);
	ft_lstadd_back(list, new);
	return (SUCCESS);
}

int	actualize_list(char *line, t_list *list)
{
	t_list	*tmp;
	char	**str;

	tmp = list;
	str = ft_split_on_equal(line);
	if (!str)
		return (ERROR);
	while (tmp && ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	free(((t_var *)tmp->content)->value);
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	if (!((t_var *)tmp->content)->value)
		return (printi_stderr(0, strerror(errno), 0));
	free_double(str);
	return (SUCCESS);
}

int	actualize_duplicate(char *arg, t_big *datas)
{
	int	ret;
	int	ret2;
	int	ret3;
	int	ret4;

	ret = actualize_list(arg, *datas->hidden);
	ret2 = SUCCESS;
	ret3 = SUCCESS;
	ret4 = SUCCESS;
	if (check_duplicate(*datas->export, arg))
		ret2 = actualize_list(arg, *datas->export);
	if (check_duplicate(*datas->env, arg))
		ret3 = actualize_list(arg, *datas->env);
	else
		ret4 = add_to_list(arg, datas->env);
	if (!ret || !ret2 || !ret3 || !ret4)
		return (ERROR);
	else
		return (SUCCESS);
}

int	ft_hidden(char **arg, t_big *datas)
{
	int	ret;
	int	k;

	k = 0;
	ret = SUCCESS;
	while (arg[k])
	{
		if (check_arg_conformity(arg[k]))
		{
			if (!check_duplicate(*datas->hidden, arg[k]))
				ret = add_to_list(arg[k], datas->hidden);
			else
				ret = actualize_duplicate(arg[k], datas);
		}
		else
		{
			tcaps.ret = 127;
			printi_stderr(arg[k], ":command not found", 1);
		}
		if (!ret)
			return (BUILT_IN_FAILURE);
		k++;
	}
	return (tcaps.ret);
}
