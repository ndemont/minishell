/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_cursor_move_down.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 19:18:07 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/16 19:18:17 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	down_first_case(int *new_c_pos)
{
	int	ret;

	ret = move_cursor(tcaps.cursor_max, tcaps.l_pos + 1);
	*new_c_pos = tcaps.cursor_max;
	return (ret);
}

int	down_second_case(int *new_c_pos)
{
	int	ret;

	ret = move_cursor(tcaps.c_pos, tcaps.l_pos + 1);
	*new_c_pos = tcaps.c_pos;
	return (ret);
}

int	move_cursor_down(void)
{
	int	ret;
	int	old_c_pos;
	int	new_c_pos;

	ret = cursor_position();
	if (!ret)
		return (ERROR);
	old_c_pos = tcaps.c_pos;
	if (tcaps.cursor_lvl == tcaps.line_lvl)
		return (SUCCESS);
	else if (tcaps.c_pos > tcaps.cursor_max && \
	tcaps.cursor_lvl + 1 == tcaps.line_lvl)
		ret = down_first_case(&new_c_pos);
	else
		ret = down_second_case(&new_c_pos);
	tcaps.cursor_pos = tcaps.cursor_pos + \
	(tcaps.c_max - old_c_pos) + new_c_pos;
	tcaps.cursor_lvl++;
	if (!ret)
		return (ERROR);
	else
		return (SUCCESS);
}
