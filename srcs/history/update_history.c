/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:58:06 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/06 14:47:10 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		update_history_file(t_big *datas)
{
	int			fd;
	t_history	*history;

	if ((fd = open(".minishell_history", O_CREAT | O_WRONLY | O_APPEND, 0644)) < 0)
		return (0);
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
