/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:09:00 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/27 11:54:12 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*browse_up_history(t_history *current, char **browse, t_big *datas)
{
	if (!datas->flag_history)
	{
		if (current && current->command)
			*browse = ft_strdup(current->command);
	}
	else
	{
		if (current->next && current->next->command && *current->next->command)
		{
			current = current->next;
			*browse = ft_strdup(current->command);
		}
	}
	datas->flag_history = 1;
	return (current);
}

t_history	*browse_down_history(t_history *current, char **browse, t_big *datas, char *input)
{

	if (datas->flag_history && current->prev && current->prev->command && *current->prev->command)
	{
		current = current->prev;
		*browse = ft_strdup(current->command);
		datas->flag_history = 1;
	}
	else 
	{
		*browse = input;
		datas->flag_history = 0;
	}
	return (current);
}

void	lines_added(char *str)
{
	int size;
	int line_len;

	tcaps.line_lvl = 0;
	size = tcaps.c_max - tcaps.c_start;
	line_len = ft_strlen(str);
	if (line_len > size)
	{
		line_len -= size;
		size = tcaps.c_max;
		tcaps.line_lvl += line_len / size;
		if (line_len % size)
			tcaps.line_lvl++;
	}
}

void	browse_history(t_big *datas, char **line, int signal)
{
	static t_history	*current = 0;
	static char			*browse;
	static char			*input;

	if (!datas->flag_history)
	{
		current = *datas->history;
		input = ft_strdup(*line);
	}
	if (signal == 1)
		current = browse_up_history(current, &browse, datas);
	if (signal == 0)
		current = browse_down_history(current, &browse, datas, input);
	if (browse)
	{
		lines_added(browse);
		ft_putstr_fd(browse, STDIN_FILENO);
		*line = browse;
	}
}