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

int	get_cursor_max(void)
{
	int	ret;

	ret = cursor_position();
	tcaps.cursor_max = tcaps.c_pos;
	return (ret);
}

void	actualize_cursor(int new_c_pos, int new_l_pos)
{
	tcaps.c_pos = new_c_pos;
	tcaps.l_pos = new_l_pos;
}

static void	actualize_some_things(int old_c_pos, int new_c_pos)
{
	tcaps.cursor_pos = tcaps.cursor_pos - old_c_pos - \
	(tcaps.c_max - new_c_pos);
	tcaps.cursor_lvl--;
}

int	cursor_up_first_case(int *new_c_pos)
{
	int	ret;

	if (tcaps.c_pos < tcaps.c_start)
	{
		ret = move_cursor(tcaps.c_start, tcaps.l_pos - 1);
		*new_c_pos = tcaps.c_start;
	}
	else
	{
		ret = move_cursor(tcaps.c_pos, tcaps.l_pos - 1);
		*new_c_pos = tcaps.c_pos;
	}
	return (ret);
}

int	move_cursor_up(void)
{
	int	ret;
	int	new_c_pos;
	int	old_c_pos;

	ret = cursor_position();
	if (!ret)
		return (ERROR);
	old_c_pos = tcaps.c_pos;
	if (!tcaps.cursor_lvl)
		return (SUCCESS);
	else if (tcaps.cursor_lvl == 1)
		ret = cursor_up_first_case(&new_c_pos);
	else
	{
		ret = move_cursor(tcaps.c_pos, tcaps.l_pos - 1);
		new_c_pos = tcaps.c_pos;
	}
	actualize_some_things(old_c_pos, new_c_pos);
	if (!ret)
		return (ERROR);
	else
		return (SUCCESS);
}
