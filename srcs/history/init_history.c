/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:15:32 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/06 12:32:10 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*new_history_elem(char *command, int status)
{
	t_history *new;

	if (!(new = (t_history *)malloc(sizeof(t_history))))
		return (0);
	if (!(new->command = ft_strdup(command)))
	{
		free(new);
		return (0);
	}
	new->status = status;
	new->prev = 0;
	new->next = 0;
	return (new);
}

void		history_add_front(t_history **begin, t_history *new)
{
	t_history *tmp;

	tmp = *begin;
	tmp->prev = new;
	new->next = tmp;
	*begin = new;
}

int			update_history_list(t_history **begin, char *line, int status)
{
	t_history	*new;

	if (!(new = new_history_elem(line, status)))
		return (0);
	history_add_front(begin, new);
	return (1);
}

int		create_history(t_big *datas)
{
	if (!(datas->history = (t_history **)malloc(sizeof(t_history))))
		return (0);
	if (!(*datas->history = (t_history *)malloc(sizeof(t_history))))
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

int		init_history(t_big *datas)
{
	int			fd;
	int			ret;
	char		*line;

	if (!(create_history(datas)))
		return (0);
	if ((fd = open(".minishell_history", O_CREAT | O_RDWR | O_APPEND, 0644)) < 0)
		return (0);
	ret = 1;
	while (ret > 0)
	{
		if ((ret = get_next_line(fd, &line)) < 0)
		{
			if (line)
				free(line);
			return (0);
		}
		if (line && *line)
		{
			if (!(update_history_list(datas->history, line, 0)))
			{
				free(line);
				return (0);
			}
		}
		if (line)
			free(line);
	}
	close(fd);
	return (1);
}
