/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:09:00 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/26 16:59:57 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*browse_up_history(t_history *current, char **browse, int begin)
{
	if (!begin)
		*browse = ft_strdup(current->command);
	else
	{
		if (current->next && current->next->command && *current->next->command)
		{
			current = current->next;
			*browse = ft_strdup(current->command);
		}
		// else 
		// 	*browse = 0;
	}
	return (current);
}

t_history	*browse_down_history(t_history *current, char **browse, int begin, char *input)
{
	if (!begin)
		*browse = ft_strdup(current->command);
	else
	{
		if (current->prev && current->prev->command && *current->prev->command)
		{
			current = current->prev;
			*browse = ft_strdup(current->command);
		}
		else 
			*browse = input;
	}
	return (current);
}

void	browse_history(t_big *datas, char **line, int signal)
{
	static char			*browse;
	static char			*input;
	static t_history	*current = 0;

	if (!datas->flag_history)
		input = ft_strdup(*line);
	if (datas->history)
		if (*datas->history && !datas->flag_history)
			current = *datas->history;
	if (signal == 1)
		current = browse_up_history(current, &browse, datas->flag_history);
	if (signal == 0)
		current = browse_down_history(current, &browse, datas->flag_history, input);
	if (browse)
	{
		ft_putstr_fd(browse, STDIN_FILENO);
		*line = browse;
	}
	datas->flag_history = 1;
}