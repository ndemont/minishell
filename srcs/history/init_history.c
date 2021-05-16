/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:15:32 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/15 17:44:51 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		create_history(t_big *datas)
{
	datas->history = (t_history **)malloc(sizeof(t_history));
	if (!(datas->history))
		return (0);
	*datas->history = (t_history *)malloc(sizeof(t_history));
	if (!(*datas->history))
	{
		free(datas->history);
		return (0);
	}
	(*datas->history)->prev = 0;
	(*datas->history)->next = 0;
	(*datas->history)->command = 0;
	(*datas->history)->status = 0;
	return (1);
}

int		copy_history(t_big *datas, int fd)
{
	int		ret;
	int		error;
	char	*line;

	ret = get_next_line(fd, &line);
	if (ret < 0)
	{
		if (line)
			free(line);
		return (ret);
	}
	if (line && *line)
	{
		error = update_history_list(datas->history, line, 0);
		if (!error)
		{
			free(line);
			return (-1);
		}
	}
	if (line)
		free(line);
	return (ret);
}

int		init_history(t_big *datas)
{
	int			fd;
	int			ret;
	int			error;

	error = create_history(datas);
	if (!error)
		return (0);
	fd = open(".minishell_history", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		return (printi_stderr(0, strerror(errno), 0));
	ret = 1;
	while (ret > 0)
	{
		ret = copy_history(datas, fd);
		if (ret < 0)
			return (0);
	}
	close(fd);
	return (1);
}
