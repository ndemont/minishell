/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:16:02 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/13 20:25:24 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_args(char **arg, t_big *datas)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (datas->redirection_arg[count])
		count++;
	while (arg && arg[i])
		i++;
	count += i;
	return (count);
}

static char		**tab_join(char **tab1, t_big *datas)
{
	int		j;
	int		i;
	int		count;
	char	**new;

	i = 0;
	j = 0;
	count = count_args(tab1, datas);
	if (!(new = (char **)malloc(sizeof(char *) * (count + 1))))
		return (printcc_stderr(0, strerror(errno), 0, 1));
	new[count] = 0;
	while (tab1 && tab1[i])
	{
		new[i] = tab1[i];
		i++;
	}
	if (tab1)
		free(tab1);
	while (i < count)
	{
		if (!(new[i] = ft_strdup(datas->redirection_arg[j])))
			return (printcc_stderr(0, strerror(errno), 0, 1));
		i++;
		j++;
	}
	return (new);
}

char	**get_arguments(t_node *root, t_big *datas)
{
	if (datas->redirection_arg)
	{
		if (!(root->arg = tab_join(root->arg, datas)))
			return (printcc_stderr(0, strerror(errno), 0, 1));
		datas->redirection_arg = 0;
	}
	return (root->arg);
}