/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:09:00 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/16 18:38:41 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		browse_history(t_big *datas, char **line, int signal)
{
	static t_history	*current = 0;

	if (!datas->flag_history)
	{
		current = *datas->history;
		if (datas->input)
			free(datas->input);
		datas->input = ft_strdup(*line);
		if (!datas->input)
			return (printi_stderr(0, strerror(errno), 0));
	}
	if (signal == 1)
	{
		current = browse_up(current, &datas->browse, datas, datas->input);
		if (!current)
			return (printi_stderr(0, "Error in history browse_up function\n", 0));
	}
	if (signal == 0)
	{
		current = browse_down(current, &datas->browse, datas, datas->input);
		if (!current)
			return (printi_stderr(0, "Error in history browse_down function\n", 0));
	}
	if (datas->browse)
	{
		lines_added(datas->browse);
		tcaps.cursor_lvl = tcaps.line_lvl;
		ft_putstr_fd(datas->browse, STDIN_FILENO);
		if (*line)
			free(*line);
		*line = ft_strdup(datas->browse);
		if (!(*line))
			return (printi_stderr(0, strerror(errno), 0));
	}
	return (1);
}
