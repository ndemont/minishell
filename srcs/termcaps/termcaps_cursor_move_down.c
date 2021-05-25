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

	ret = move_cursor(g_tcaps.cursor_max, g_tcaps.l_pos + 1);
	*new_c_pos = g_tcaps.cursor_max;
	return (ret);
}

int	down_second_case(int *new_c_pos)
{
	int	ret;

	ret = move_cursor(g_tcaps.c_pos, g_tcaps.l_pos + 1);
	*new_c_pos = g_tcaps.c_pos;
	return (ret);
}

int	move_cursor_down(void)
{
	int	ret;
	int	old_c_pos;
	int	new_c_pos;

	old_c_pos = g_tcaps.c_pos;
	if (g_tcaps.cursor_lvl == g_tcaps.line_lvl)
		return (SUCCESS);
	else if (g_tcaps.c_pos > g_tcaps.cursor_max && \
	g_tcaps.cursor_lvl + 1 == g_tcaps.line_lvl)
		ret = down_first_case(&new_c_pos);
	else
		ret = down_second_case(&new_c_pos);
	g_tcaps.cursor_pos = g_tcaps.cursor_pos + \
	(g_tcaps.c_max - old_c_pos) + new_c_pos;
	g_tcaps.cursor_lvl++;
	if (!ret)
		return (ERROR);
	else
		return (SUCCESS);
}
