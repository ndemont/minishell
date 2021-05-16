/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_up_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:47:50 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/16 18:39:13 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cmp_history(char **browse, t_history *tmp)
{
	if (*browse)
		free(*browse);
	*browse = ft_strdup(tmp->command);
	if (!(*browse))
		return (printi_stderr(0, strerror(errno), 0));
	return (1);
}

t_history	*new_up(t_history *going, char **browse, char *str)
{
	int			len;
	int			ret;
	t_history	*tmp;
	char		*address;

	tmp = going;
	while (tmp && tmp->command)
	{
		len = ft_strlen(tmp->command);
		address = ft_strnstr(tmp->command, str, len);
		if (address == tmp->command)
		{
			ret = cmp_history(browse, tmp);
			if (!ret)
				return (ERROR);
			going = tmp;
			return (going);
		}
		tmp = tmp->next;
	}
	return (going);
}

t_history	*next_up(t_history *going, char **browse, char *str)
{
	int			len;
	int			ret;
	t_history	*tmp;
	char		*address;

	tmp = going;
	while (tmp->next && tmp->next->command && *tmp->next->command)
	{
		len = ft_strlen(tmp->next->command);
		tmp = tmp->next;
		address = ft_strnstr(tmp->command, str, len);
		if (address == tmp->command)
		{
			ret = cmp_history(browse, tmp);
			if (!ret)
				return (ERROR);
			going = tmp;
			return (going);
		}
	}
	return (going);
}

t_history	*browse_up(t_history *going, char **browse, t_big *datas, char *str)
{
	if (!datas->flag_history)
		going = new_up(going, browse, str);
	else
		going = next_up(going, browse, str);
	datas->flag_history = 1;
	return (going);
}
