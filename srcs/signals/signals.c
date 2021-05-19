/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 13:47:33 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/18 15:17:48 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signals(int sig)
{
	int	level;
	int	ret;

	if (sig == SIGINT)
	{
		level = g_tcaps.l_pos + (g_tcaps.line_lvl - g_tcaps.cursor_lvl);
		ret = move_cursor(g_tcaps.cursor_max, level);
		if (!ret)
			return ;
		write(0, "\n", 1);
		if (!g_tcaps.child)
		{
			g_tcaps.signal = 1;
			display_prompt();
		}
	}
	if (sig == SIGQUIT)
	{
		if (g_tcaps.child)
			write(0, "Quit: 3\n", 8);
	}
}
