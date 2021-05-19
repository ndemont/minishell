/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:09:00 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/19 11:12:48 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lines_added(char *str)
{
	int	size;
	int	line_len;

	g_tcaps.line_lvl = 0;
	size = g_tcaps.c_max - g_tcaps.c_start;
	line_len = ft_strlen(str);
	if (line_len > size)
	{
		line_len -= size;
		size = g_tcaps.c_max;
		g_tcaps.line_lvl += line_len / size;
		if (line_len % size)
			g_tcaps.line_lvl++;
	}
}

int	actualize_line(char **line, t_big *datas)
{
	if (datas->browse)
	{
		lines_added(datas->browse);
		g_tcaps.cursor_lvl = g_tcaps.line_lvl;
		ft_putstr_fd(datas->browse, STDIN_FILENO);
		if (*line)
			free(*line);
		*line = ft_strdup(datas->browse);
		if (!(*line))
			return (printi_stderr(0, strerror(errno), 0));
	}
	return (1);
}

t_history	*initialize_browsing(t_big *datas, char **line, t_history *current)
{
	if (!datas->flag_history)
	{
		current = *datas->history;
		if (datas->input)
			free(datas->input);
		datas->input = ft_strdup(*line);
		if (!datas->input)
		{
			printi_stderr(0, strerror(errno), 0);
			return (0);
		}
	}
	return (current);
}

int	browse_history(t_big *datas, char **line, int signal)
{
	static t_history	*current = 0;
	int					ret;

	current = initialize_browsing(datas, line, current);
	if (!current)
		return (ERROR);
	if (signal == 1)
	{
		current = browse_up(current, &datas->browse, datas, datas->input);
		if (!current)
			return (ERROR);
	}
	if (signal == 0)
	{
		current = browse_down(current, &datas->browse, datas, datas->input);
		if (!current)
			return (ERROR);
	}
	ret = actualize_line(line, datas);
	if (!ret)
		return (0);
	return (1);
}
