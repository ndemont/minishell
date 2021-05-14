/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_cursor_moves.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:43:52 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/03 20:44:00 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		get_cursor_max(void)
{
	cursor_position();
	tcaps.cursor_max = tcaps.c_pos;
}

void		actualize_cursor(int new_c_pos, int new_l_pos)
{
	tcaps.c_pos = new_c_pos;
	tcaps.l_pos = new_l_pos;
}

static void	actualize_some_things(int new_c_pos)
{
	tcaps.cursor_pos = tcaps.cursor_pos - tcaps.c_pos - \
	(tcaps.c_max - new_c_pos);
	tcaps.cursor_lvl--;
}

void		move_cursor_up(void)
{
	int new_c_pos;

	cursor_position();
	if (!tcaps.cursor_lvl)
		return ;
	else if (tcaps.cursor_lvl == 1)
	{
		if (tcaps.c_pos < tcaps.c_start)
		{
			move_cursor(tcaps.c_start, tcaps.l_pos - 1);
			new_c_pos = tcaps.c_start;
		}
		else
		{
			move_cursor(tcaps.c_pos, tcaps.l_pos - 1);
			new_c_pos = tcaps.c_pos;
		}
	}
	else
	{
		move_cursor(tcaps.c_pos, tcaps.l_pos - 1);
		new_c_pos = tcaps.c_pos;
	}
	actualize_some_things(new_c_pos);
}

void		move_cursor_down(void)
{
	int	new_c_pos;

	cursor_position();
	if (tcaps.cursor_lvl == tcaps.line_lvl)
		return ;
	else if (tcaps.c_pos > tcaps.cursor_max && \
	tcaps.cursor_lvl + 1 == tcaps.line_lvl)
	{
		move_cursor(tcaps.cursor_max, tcaps.l_pos + 1);
		new_c_pos = tcaps.cursor_max;
	}
	else
	{
		move_cursor(tcaps.c_pos, tcaps.l_pos + 1);
		new_c_pos = tcaps.c_pos;
	}
	tcaps.cursor_pos = tcaps.cursor_pos + \
	(tcaps.c_max - tcaps.c_pos) + new_c_pos;
	tcaps.cursor_lvl++;
}
