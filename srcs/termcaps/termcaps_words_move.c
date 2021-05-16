/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_words_move.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:41:23 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/05 10:41:31 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ghost_move_cursor_left(int *c_pos, int *l_pos)
{
	if ((*c_pos - 1 >= tcaps.c_start && !tcaps.cursor_lvl) || \
	(*c_pos - 1 >= 0 && tcaps.cursor_lvl))
		(*c_pos)--;
	else if (*c_pos - 1 < 0 && tcaps.cursor_lvl)
	{
		*c_pos = tcaps.c_max - 1;
		(*l_pos)--;
		tcaps.cursor_lvl--;
	}
}

void	ghost_move_cursor_right(int *c_pos, int *l_pos)
{
	if (tcaps.cursor_lvl == tcaps.line_lvl)
	{
		if (*c_pos + 1 <= tcaps.cursor_max)
			(*c_pos)++;
	}
	else if (tcaps.cursor_lvl < tcaps.line_lvl)
	{
		if (*c_pos + 1 < tcaps.c_max)
			(*c_pos)++;
		else
		{
			*c_pos = 0;
			(*l_pos)++;
			tcaps.cursor_lvl++;
		}
	}
}

void	word_left(char **line)
{
	int next_c_pos;
	int next_l_pos;

	next_c_pos = tcaps.c_pos;
	next_l_pos = tcaps.l_pos;
	if ((*line)[tcaps.cursor_pos] && tcaps.cursor_pos - 1 >= 0 && (*line)[tcaps.cursor_pos] > 32 && \
	(*line)[tcaps.cursor_pos] < 127 && (*line)[tcaps.cursor_pos - 1] == ' ') \
	|| (tcaps.cursor_pos > 0 && tcaps.c_pos == tcaps.cursor_max))
	{
		ghost_move_cursor_left(&next_c_pos, &next_l_pos);
		tcaps.cursor_pos--;
	}
	while (tcaps.cursor_pos > 0 && (*line)[tcaps.cursor_pos] && (*line)[tcaps.cursor_pos] == ' ')
	{
		ghost_move_cursor_left(&next_c_pos, &next_l_pos);
		tcaps.cursor_pos--;
	}
	while (tcaps.cursor_pos - 1 >= 0 && (*line)[tcaps.cursor_pos] && (*line)[tcaps.cursor_pos - 1] > 32 &&
	(*line)[tcaps.cursor_pos - 1] < 127)
	{
		ghost_move_cursor_left(&next_c_pos, &next_l_pos);
		tcaps.cursor_pos--;
	}
	move_cursor(next_c_pos, next_l_pos);
}

void	word_right(int *i, char **line)
{
	int next_c_pos;
	int next_l_pos;

	next_c_pos = tcaps.c_pos;
	next_l_pos = tcaps.l_pos;
	while (tcaps.cursor_pos < (*i) && (*line)[tcaps.cursor_pos] && (*line)[tcaps.cursor_pos] > 32 && \
	(*line)[tcaps.cursor_pos] < 127)
	{
		ghost_move_cursor_right(&next_c_pos, &next_l_pos);
		tcaps.cursor_pos++;
	}
	while (tcaps.cursor_pos < *i && (*line)[tcaps.cursor_pos] && (*line)[tcaps.cursor_pos] == ' ')
	{
		ghost_move_cursor_right(&next_c_pos, &next_l_pos);
		tcaps.cursor_pos++;
	}
	move_cursor(next_c_pos, next_l_pos);
}
