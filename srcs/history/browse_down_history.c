/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_down_history.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:48:26 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/16 18:44:12 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*next_down(t_history *current, char **browse, char *input)
{
	int			len;
	char		*address;
	t_history	*tmp;

	tmp = current;
	while (tmp->prev && tmp->prev->command && *tmp->prev->command)
	{
		len = ft_strlen(tmp->prev->command);
		address = ft_strnstr(tmp->prev->command, input, len);
		tmp = tmp->prev;
		if (address == tmp->command)
		{
			if (*browse)
				free(*browse);
			*browse = ft_strdup(tmp->command);
			if (!(*browse))
				return (printi_stderr(0, strerror(errno), 0));
			current = tmp;
			return (current);
		}
	}
	return (current);
}

t_history	*last_down(t_history *going, char **browse, char *str)
{
	if (*browse)
		free(*browse);
	*browse = ft_strdup(str);
	if (!(*browse))
		return (printi_stderr(0, strerror(errno), 0));
	return (going);
}

t_history	*browse_down(t_history *going, char **brws, t_big *datas, char *str)
{
	if (datas->flag_history && going->prev && going->prev->command \
	&& *going->prev->command)
	{
		going = next_down(going, brws, str);
		datas->flag_history = 1;
	}
	else
	{
		going = last_down(going, brws, str);
		datas->flag_history = 0;
	}
	return (going);
}
