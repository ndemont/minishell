/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:09:00 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/23 14:31:59 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*browse_up_history(t_history *current, char *line, char *browse)
{
	t_history	*list;
	char		*address;

	list = current;
	if (!line)
	{
		browse = current->command;
		current = current->next;
		return (current);
	}
	while (list->next)
	{
		address = ft_strnstr(list->command, line, ft_strlen(list->command));
		if (!address || address != list->command)
			list = list->next;
		else
		{
			current = list;
			browse = list->command;
			break ;
		}
	}
	return (current);
}

t_history	*browse_down_history(t_history *current, char *line, char *browse)
{
	t_history	*list;
	char		*address;

	list = current;
	if (!line)
	{
		browse = current->command;
		current = current->prev;
		return (current);
	}
	while (list->prev)
	{
		address = ft_strnstr(list->command, line, ft_strlen(list->command));
		if (!address || address != list->command)
			list = list->prev;
		else
		{
			current = list;
			browse = list->command;
			break ;
		}
	}
	return (current);
}

void		browse_history(t_big *datas, char *line, int signal)
{
	char		*browse;
	t_history	*current;

	browse = 0;
	current = *datas->history;
	while (signal >= 0)
	{
		if (signal == 1)
			current = browse_up_history(current, line, browse);
		if (signal == 0)
			current = browse_down_history(current, line, browse);
		//delete line
		write(1, browse, ft_strlen(browse));
	}
}