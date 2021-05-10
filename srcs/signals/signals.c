/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 13:47:33 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/27 22:21:38 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signals(int sig)
{
	if (sig == SIGINT)
	{
		move_cursor(tcaps.cursor_max, tcaps.l_pos + (tcaps.line_lvl - tcaps.cursor_lvl));
		write(0, "\n", 1);
		if (!tcaps.child)
		{
			tcaps.signal = 1;
			display_prompt();
		}
	}
	if (sig == SIGQUIT)
	{
		if (tcaps.child)
			write(0, "Quit: 3\n", 8);
	}

}