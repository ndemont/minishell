/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:16:02 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/20 22:50:04 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **arg, t_big *datas)
{
	int	count;
	int j;
	int	i;

	i = 0;
	j = 0;
	count = 0;
	if (datas->redirection_arg)
	{
		while (datas->redirection_arg[count] && datas->redirection_arg[count][0])
			j++;
		count++;
	}
	while (arg && arg[i])
	{
		if (arg[i] && arg[i][0])
			j++;
		i++;
	}
	return (j);
}

static char	**init_tab(char **tab1, t_big *datas)
{
	int		count;
	char	**new;

	count = count_args(tab1, datas);
	new = (char **)malloc(sizeof(char *) * (count + 1));
	if (!(new))
		return (printcc_stderr(0, strerror(errno), 0));
	new[count] = 0;
	return (new);
}

static char	**tab_join(char **tab1, t_big *datas)
{
	int		j;
	int		i;
	char	**new;

	i = 0;
	j = 0;
	new = init_tab(tab1, datas);
	if (!new)
		return (0);
	while (tab1 && tab1[i])
	{
		if (tab1[i][0])
		{
			new[j] = tab1[i];
			j++;
		}
		//else
		//	free(tab1[i]);
		i++;
	}
	if (tab1)
		free(tab1);
	i = 0;
	while (datas->redirection_arg && datas->redirection_arg[i])
	{
		if (datas->redirection_arg[i][0])
		{
			new[j] = ft_strdup(datas->redirection_arg[i]);
			if (!(new[j]))
				return (printcc_stderr(0, strerror(errno), 0));
			j++;
		}
		i++;
	}
	return (new);
}

char	**get_arguments(t_node *root, t_big *datas)
{
	root->arg = tab_join(root->arg, datas);
	if (!(root->arg))
		return (printcc_stderr(0, strerror(errno), 0));
	datas->redirection_arg = 0;
	return (root->arg);
}
