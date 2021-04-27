/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:58:06 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/27 15:19:51 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_history_file(t_big *datas)
{
	int			fd;
	t_history	*history;
	
	fd = open(".minishell_history", O_CREAT | O_WRONLY | O_APPEND, 0644);
	history = 0;
	if (datas->history)
		history = *datas->history;
	while (history && history->next->status != 0)
		history = history->next;
	while (history)
	{
		write(fd, history->command, ft_strlen(history->command));
		write(fd, "\n", 1);
		history = history->prev;
	}
	close(fd);
}