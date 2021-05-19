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
	if ((*c_pos - 1 >= g_tcaps.c_start && !g_tcaps.cursor_lvl) || \
	(*c_pos - 1 >= 0 && g_tcaps.cursor_lvl))
		(*c_pos)--;
	else if (*c_pos - 1 < 0 && g_tcaps.cursor_lvl)
	{
		*c_pos = g_tcaps.c_max - 1;
		(*l_pos)--;
		g_tcaps.cursor_lvl--;
	}
}

void	ghost_move_cursor_right(int *c_pos, int *l_pos)
{
	if (g_tcaps.cursor_lvl == g_tcaps.line_lvl)
	{
		if (*c_pos + 1 <= g_tcaps.cursor_max)
			(*c_pos)++;
	}
	else if (g_tcaps.cursor_lvl < g_tcaps.line_lvl)
	{
		if (*c_pos + 1 < g_tcaps.c_max)
			(*c_pos)++;
		else
		{
			*c_pos = 0;
			(*l_pos)++;
			g_tcaps.cursor_lvl++;
		}
	}
}

void	move_register_ghost_pos(int *next_c_pos, int *next_l_pos)
{
	ghost_move_cursor_left(next_c_pos, next_l_pos);
	g_tcaps.cursor_pos--;
}

int	word_left(char **line)
{
	int	next_c_pos;
	int	next_l_pos;

	next_c_pos = g_tcaps.c_pos;
	next_l_pos = g_tcaps.l_pos;
	if (((*line)[g_tcaps.cursor_pos] && g_tcaps.cursor_pos - 1 >= 0 && \
	(*line)[g_tcaps.cursor_pos] > 32 && (*line)[g_tcaps.cursor_pos] < 127 && \
	(*line)[g_tcaps.cursor_pos - 1] == ' ') || \
	(g_tcaps.cursor_pos > 0 && g_tcaps.c_pos == g_tcaps.cursor_max))
		move_register_ghost_pos(&next_c_pos, &next_l_pos);
	while (g_tcaps.cursor_pos > 0 && (*line)[g_tcaps.cursor_pos] && \
	(*line)[g_tcaps.cursor_pos] == ' ')
		move_register_ghost_pos(&next_c_pos, &next_l_pos);
	while (g_tcaps.cursor_pos - 1 >= 0 && (*line)[g_tcaps.cursor_pos] && \
	(*line)[g_tcaps.cursor_pos - 1] > 32 && \
	(*line)[g_tcaps.cursor_pos - 1] < 127)
		move_register_ghost_pos(&next_c_pos, &next_l_pos);
	return (move_cursor(next_c_pos, next_l_pos));
}

int	word_right(int *i, char **line)
{
	int	next_c_pos;
	int	next_l_pos;

	next_c_pos = g_tcaps.c_pos;
	next_l_pos = g_tcaps.l_pos;
	while (g_tcaps.cursor_pos < (*i) && (*line)[g_tcaps.cursor_pos] && \
	(*line)[g_tcaps.cursor_pos] > 32 && (*line)[g_tcaps.cursor_pos] < 127)
	{
		ghost_move_cursor_right(&next_c_pos, &next_l_pos);
		g_tcaps.cursor_pos++;
	}
	while (g_tcaps.cursor_pos < *i && (*line)[g_tcaps.cursor_pos] && \
	(*line)[g_tcaps.cursor_pos] == ' ')
	{
		ghost_move_cursor_right(&next_c_pos, &next_l_pos);
		g_tcaps.cursor_pos++;
	}
	return (move_cursor(next_c_pos, next_l_pos));
}
