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
	int ret;

	ret = move_cursor(tcaps.c_start, tcaps.l_pos - tcaps.cursor_lvl);
	if (!ret)
		return (ERROR);
	tcaps.cursor_lvl = 0;
	ret = clear_after_cursor();
	if (!ret)
		return (ERROR);
	ret = browse_history(datas, line, flag);
	if (!ret)
		return (ERROR);
	*i = ft_strlen(*line);
	tcaps.cursor_pos = *i;
	ret = get_cursor_max();
	tcaps.cursor_lvl = tcaps.line_lvl;
	return (ret);
}

int	go_home(void)
{
	int ret;
	
	ret = move_cursor(tcaps.c_start, tcaps.l_pos - tcaps.cursor_lvl);
	tcaps.cursor_lvl = 0;
	tcaps.cursor_pos = 0;
	return (ret);
}

int	go_end(int *i)
{
	int ret;

	ret = move_cursor(tcaps.cursor_max, tcaps.l_pos + \
	(tcaps.line_lvl - tcaps.cursor_lvl));
	tcaps.cursor_lvl = tcaps.line_lvl;
	tcaps.cursor_pos = *i;
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
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59 &&
	buf[4] == 53 && buf[5] == 65)
		move_cursor_up();
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59 &&
	buf[4] == 53 && buf[5] == 66)
		move_cursor_down();
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59 &&
	buf[4] == 53 && buf[5] == 68)
		word_left(line);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 49 && buf[3] == 59 &&
	buf[4] == 53 && buf[5] == 67)
		word_right(i, line);
	return (SUCCESS);
}

int	do_the_right_thing(int *i, char *buf, char **line, t_big *datas)
{
	int ret;

	ret = cursor_position();
	if (!ret)
		return (ERROR);
	if (buf[0] == 127 && tcaps.cursor_pos == *i)
		return (backspace(i, line));
	else if (buf[0] == 127 && tcaps.cursor_pos < *i && tcaps.cursor_pos > 0)
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
		return(do_the_right_thing2(i, buf, line));
}
