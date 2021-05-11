/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:09:00 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/11 16:27:41 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*browse_up(t_history *current, char **browse, t_big *datas, char *input)
{
	int			len;
	t_history	*tmp;
	char		*address;

	if (!datas->flag_history)
	{
		tmp = current;
		while (tmp && tmp->command)
		{
			len = ft_strlen(tmp->command);
			address = ft_strnstr(tmp->command, input, len);
			if (address == tmp->command)
			{
				datas->flag_history = 1;
				if (*browse)
					free(*browse);
				if (!(*browse = ft_strdup(tmp->command)))
					return (0);
				current = tmp;
				return (current);
			}
			tmp = tmp->next;
		}
	}
	else
	{
		tmp = current;
		while (tmp->next && tmp->next->command && *tmp->next->command)
		{
			len = ft_strlen(tmp->next->command);
			tmp = tmp->next;
			address = ft_strnstr(tmp->command, input, len);
			if (address == tmp->command)
			{
				datas->flag_history = 1;
				if (*browse)
					free(*browse);
				if (!(*browse = ft_strdup(tmp->command)))
					return (0);
				current = tmp;
				return (current);
			}
		}
	}
	datas->flag_history = 1;
	return (current);
}

t_history	*browse_down(t_history *current, char **browse, t_big *datas, char *input)
{
	int			len;
	t_history	*tmp;
	char		*address;

	if (datas->flag_history && current->prev && current->prev->command && *current->prev->command)
	{
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
				current = tmp;
				datas->flag_history = 1;
				return (current);
			}
		}
	}
	else
	{
		if (*browse)
			free(*browse);
		*browse = ft_strdup(input);
		datas->flag_history = 0;
	}
	return (current);
}

void		lines_added(char *str)
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

void		browse_history(t_big *datas, char **line, int signal)
{
	static t_history	*current = 0;

	if (!datas->flag_history)
	{
		current = *datas->history;
		if (datas->input)
			free(datas->input);
		datas->input = ft_strdup(*line);
	}
	if (signal == 1)
		current = browse_up(current, &datas->browse, datas, datas->input);
	if (signal == 0)
		current = browse_down(current, &datas->browse, datas, datas->input);
	if (datas->browse)
	{
		lines_added(datas->browse);
		tcaps.cursor_lvl = tcaps.line_lvl;
		ft_putstr_fd(datas->browse, STDIN_FILENO);
		if (*line)
			free(*line);
		*line = ft_strdup(datas->browse);
	}
}
