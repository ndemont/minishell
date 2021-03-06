/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:51:10 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/27 21:46:42 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	history_older(int *i, char **line, t_big *datas, int flag)
{
	int	ret;

	ret = move_cursor(g_tcaps.c_start, g_tcaps.l_pos - g_tcaps.cursor_lvl);
	if (!ret)
		return (ERROR);
	g_tcaps.cursor_lvl = 0;
	ret = clear_after_cursor();
	if (!ret)
		return (ERROR);
	ret = browse_history(datas, line, flag);
	if (!ret)
		return (ERROR);
	*i = ft_strlen(*line);
	g_tcaps.cursor_pos = *i;
	ret = get_cursor_max();
	g_tcaps.cursor_lvl = g_tcaps.line_lvl;
	return (ret);
}

int	go_home(void)
{
	int	ret;

	ret = move_cursor(g_tcaps.c_start, g_tcaps.l_pos - g_tcaps.cursor_lvl);
	g_tcaps.cursor_lvl = 0;
	g_tcaps.cursor_pos = 0;
	return (ret);
}

int	go_end(int *i)
{
	int	ret;

	ret = move_cursor(g_tcaps.cursor_max, g_tcaps.l_pos + \
	(g_tcaps.line_lvl - g_tcaps.cursor_lvl));
	g_tcaps.cursor_lvl = g_tcaps.line_lvl;
	g_tcaps.cursor_pos = *i;
	return (ret);
}

int	do_the_right_thing2(int *i, char *buf, char **line)
{
	if (buf[0] > 31 && buf[0] < 127)
		return (add_at_cursor(buf[0], i, line));
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 72)
		return (go_home());
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 70)
		return (go_end(i));
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59 && \
	buf[4] == 53 && buf[5] == 65)
		return (move_cursor_up());
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59 && \
	buf[4] == 53 && buf[5] == 66)
		return (move_cursor_down());
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59 && \
	buf[4] == 53 && buf[5] == 68)
		return (word_left(line));
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59 && \
	buf[4] == 53 && buf[5] == 67)
		return (word_right(i, line));
	return (SUCCESS);
}

int	do_the_right_thing(int *i, char *buf, char **line, t_big *datas)
{
	if (buf[0] == 127 && g_tcaps.cursor_pos == *i)
		return (backspace(i, line));
	else if (buf[0] == 127 && g_tcaps.cursor_pos < *i && g_tcaps.cursor_pos > 0)
		return (backspace_at_cursor(i, line));
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		return (history_older(i, line, datas, 1));
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		return (history_older(i, line, datas, 0));
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		return (move_cursor_left());
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		return (move_cursor_right());
	else if (buf[0] == 12)
		return (clear_term());
	else if (buf[0] == 4)
		return (ctrl_d(datas, line, i));
	else
		return (do_the_right_thing2(i, buf, line));
}
