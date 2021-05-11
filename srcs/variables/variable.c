/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:16:02 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/11 23:11:52 by ndemont          ###   ########.fr       */
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
	while (arg[i])
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
		return (print_stderr(0, strerror(errno), 0, 1));
	new[count] = 0;
	while (tab1[i])
	{
		new[i] = tab1[i];
		i++;
	}
	free(tab1);
	while (i < count)
	{
		if (!(new[i] = ft_strdup(datas->redirection_arg[j])))
			return (print_stderr(0, strerror(errno), 0, 1));
		i++;
		j++;
	}
	return (new);
}

char	**replace_variable(char **arg, char *cmd, t_big *datas)
{
	(void)cmd;
	if (datas->redirection_arg)
	{
		if (!(arg = tab_join(arg, datas)))
			return (print_stderr(0, strerror(errno), 0, 1));
		datas->redirection_arg = 0;
	}
	return (arg);
}