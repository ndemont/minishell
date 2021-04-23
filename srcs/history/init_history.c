/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:15:32 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/23 20:00:19 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*new_history_elem(char *command, int status)
{
	t_history *new;

	new = (t_history *)malloc(sizeof(t_history));
	new->command = command;
	new->status = status;
	new->prev = 0;
	new->next = 0;
	return (new);
}

void		history_add_front(t_history **begin, t_history *new)
{
	new->next = *begin;
	(*begin)->prev = new;
	*begin = new;
}

void		update_history(t_history **begin, char *line, int status)
{
	t_history	*new;

	new = new_history_elem(line, status);
	history_add_front(begin, new);
}

void		create_history(t_big *datas)
{
	datas->history = (t_history **)malloc(sizeof(t_history));
	*datas->history = (t_history *)malloc(sizeof(t_history));
	(*datas->history)->prev = 0;
	(*datas->history)->next = 0;
	(*datas->history)->command = 0;
	(*datas->history)->status = 0;
}

void		init_history(t_big *datas)
{
	int			fd;
	int			ret;
	char		*line;

	create_history(datas);
	fd = open(".minishell_history", O_CREAT | O_RDWR | O_APPEND, 0644);
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		update_history(datas->history, line, 0);
		ret = get_next_line(fd, &line);
	}
	close(fd);
}