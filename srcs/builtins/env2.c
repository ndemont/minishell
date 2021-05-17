/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:28:54 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/17 12:28:56 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_shell_lvl(char **level, t_list **new, t_var **tmp2)
{
	(*tmp2)->var = NULL;
	(*tmp2)->value = NULL;
	*level = ft_itoa(1);
	if (!(*level))
		return (printi_stderr(0, strerror(errno), 0));
	(*tmp2)->var = ft_strdup("SHLVL");
	if (!(*tmp2)->var)
	{
		clean_if_mallocked(level, &((*tmp2)->var), &((*tmp2)->value));
		return (printi_stderr(0, strerror(errno), 0));
	}
	(*tmp2)->value = ft_strdup(*level);
	if (!(*tmp2)->value)
	{
		clean_if_mallocked(level, &((*tmp2)->var), &((*tmp2)->value));
		return (printi_stderr(0, strerror(errno), 0));
	}
	*new = ft_lstnew(tmp2);
	if (!(*new))
	{
		clean_if_mallocked(level, &((*tmp2)->var), &((*tmp2)->value));
		return (printi_stderr(0, strerror(errno), 0));
	}
	return (SUCCESS);
}

void	shlvl_to_list(t_list *tmp, t_list **new)
{
	if (!tmp)
		tmp = *new;
	else
	{
		ft_lstadd_back(&tmp, *new);
		ft_lst_sort(tmp, &cmp_list);
	}
}

int	create_and_initiate_elem(char **level, t_list **new, t_list *tmp)
{
	int		ret;
	t_var	*tmp2;

	tmp2 = (t_var *)malloc(sizeof(t_var));
	if (!(tmp2))
		return (printi_stderr(0, strerror(errno), 0));
	ret = create_shell_lvl(level, new, &tmp2);
	if (ret)
		shlvl_to_list(tmp, new);
	return (ret);
}

int	change_shell_lvl(t_list **tmp)
{
	char	*level;
	t_list	*roam;
	t_list	*new;
	t_list	*start;

	start = *tmp;
	roam = *tmp;
	level = NULL;
	new = NULL;
	while (roam && ft_strcmp(((t_var *)(roam->content))->var, "SHLVL"))
		roam = roam->next;
	if (roam && !ft_strcmp(((t_var *)(roam->content))->var, "SHLVL"))
		increment_shell_lvl(&level, roam);
	else
		create_and_initiate_elem(&level, &new, start);
	clean_free(&level);
	return (SUCCESS);
}

int	shell_lvl(t_big *datas)
{
	int	ret1;
	int	ret2;
	int	ret3;

	ret1 = change_shell_lvl(datas->env);
	ret2 = change_shell_lvl(datas->export);
	ret3 = change_shell_lvl(datas->hidden);
	if (!ret1 || !ret2 || !ret3)
		return (ERROR);
	return (SUCCESS);
}
