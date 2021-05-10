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

void	history_older(int *i, char **line, t_big *datas, int flag)
{
	while (tcaps.cursor_lvl)
	{
		move_cursor(0, tcaps.l_pos--);
		tcaps.cursor_lvl--;
	}
	move_cursor(tcaps.c_start, tcaps.l_pos);
	clear_after_cursor();
	browse_history(datas, line, flag);
	*i = ft_strlen(*line);
	tcaps.cursor_pos = *i;
	cursor_position();
	tcaps.cursor_max = tcaps.c_pos;
}

void	go_home(void)
{
	move_cursor(tcaps.c_start, tcaps.l_pos - tcaps.cursor_lvl);
	tcaps.cursor_lvl = 0;
	tcaps.cursor_pos = 0;
}

void	go_end(int *i)
{
	move_cursor(tcaps.cursor_max, tcaps.l_pos + (tcaps.line_lvl - tcaps.cursor_lvl));
	tcaps.cursor_lvl = tcaps.line_lvl;
	tcaps.cursor_pos = *i;
}

void	do_the_right_thing(int *i, char *buf, char **line, t_big *datas)
{
	int sig;
	
	sig = 0;
	cursor_position();
	if(buf[0] == 127 && tcaps.cursor_pos == *i)
		backspace(i, line);
	else if(buf[0] == 127 && tcaps.cursor_pos < *i && tcaps.cursor_pos > 0)
		backspace_at_cursor(i, line);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		history_older(i, line, datas, 1);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		history_older(i, line, datas, 0);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		move_cursor_left();
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		move_cursor_right();
	else if (buf[0] == 12)
		clear_term();
	else if (buf[0] == 4)
		ctrl_d(datas, line, i);
	else if (buf[0] > 31 && buf[0] < 127)
		add_at_cursor(buf[0], i, line);
	else if	(buf[0] == 27 && buf[1] == 91 && buf[2] == 72)
		go_home();
	else if(buf[0] == 27 && buf[1]== 91 && buf[2] == 70)
		go_end(i);
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
}
