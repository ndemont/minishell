/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:58:06 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/15 17:37:31 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		history_add_front(t_history **begin, t_history *new)
{
	t_history *tmp;

	tmp = *begin;
	tmp->prev = new;
	new->next = tmp;
	*begin = new;
}

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

int			update_history_file(t_big *datas)
{
	int			fd;
	t_history	*history;

	fd = open(".minishell_history", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (printi_stderr(0, strerror(errno), 0));
	history = 0;
	if (datas->history)
		history = *datas->history;
	while (history && history->next && history->next->status != 0)
		history = history->next;
	while (history)
	{
		if (history->command)
			write(fd, history->command, ft_strlen(history->command));
		write(fd, "\n", 1);
		history = history->prev;
	}
	close(fd);
	return (1);
}

int			update_history_list(t_history **begin, char *line, int status)
{
	t_history	*new;

	if (!(new = new_history_elem(line, status)))
		return (0);
	history_add_front(begin, new);
	return (1);
}
