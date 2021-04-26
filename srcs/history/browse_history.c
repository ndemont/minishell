/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:09:00 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/26 14:28:05 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*browse_up_history(t_history *current, char *line, char **browse)
{
	t_history	*list;
	char		*address;

	list = current;
	(void)address;
	(void)line;
	*browse = ft_strdup(current->command);
	if (current->next && current->next->command)
		current = current->next;
	return (current);
	// while (list->next)
	// {
	// 	address = ft_strnstr(list->command, line, ft_strlen(list->command));
	// 	if (!address || address != list->command)
	// 		list = list->next;
	// 	else
	// 	{
	// 		current = list->next;
	// 		browse = list->command;
	// 		return (current);
	// 	}
	// }
	// return (0);
}

t_history	*browse_down_history(t_history *current, char *line, char **browse)
{
	t_history	*list;
	char		*address;

	list = current;
	(void)address;
	(void)line;
	*browse = current->command;
	if (current->prev && current->prev->command)
		current = current->prev;
	return (current);
	// while (list->prev)
	// {
	// 	address = ft_strnstr(list->command, line, ft_strlen(list->command));
	// 	if (!address || address != list->command)
	// 		list = list->prev;
	// 	else
	// 	{
	// 		current = list->prev;
	// 		browse = list->command;
	// 		return (current);
	// 	}
	// }
	return (0);
}

void	browse_history(t_big *datas, char **line, int signal)
{
	char				*browse;
	static	char		*prev_browse = "";
	static t_history	*current = 0;

	browse = 0;
	if (datas->history)
		if (*datas->history && !datas->flag_history)
			current = *datas->history;
	datas->flag_history = 1;
	if (signal == 1)
		current = browse_up_history(current, *line, &browse);
	if (signal == 0)
		current = browse_down_history(current, *line, &browse);
	if (ft_strcmp(browse, prev_browse))
		printf("%s\n", browse);
	prev_browse = browse;
	*line = browse;
}