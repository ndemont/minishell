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

void	raw_mode(void)
{
	tcgetattr(STDIN_FILENO, &tcaps.save);
	tcaps.term = tcaps.save;
	tcaps.term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tcaps.term);
}

void	normal_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tcaps.save);
}

void	termcaps_init(void)
{
	int ret;
	char *term;

	term = getenv("TERM");

	if ((ret = tgetent(NULL, term)) <= 0)
		exit(0); // changer methode d'exit
}

void	term_size(void)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
    tcaps.l_max = w.ws_row;
    tcaps.c_max = w.ws_col;
	//tcaps.c_max = tgetnum("co");
	//tcaps.l_max = tgetnum("li");
}

void	cursor_position(void)
{
	char buf[100];
	int i;

	term_size();
	write(1, "\033[6n", 4);
	read(1, buf, 100);
	i = 0;
	while(i < 100 && !ft_isdigit(buf[i]))
		i++;
	tcaps.l_pos = ft_atoi(buf + i) - 1;
	while(i < 100 && ft_isdigit(buf[i]))
		i++;
	while(i < 100 && !ft_isdigit(buf[i]))
		i++;
	tcaps.c_pos = ft_atoi(buf + i) - 1;
}

int		ft_putchar2(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void	move_cursor(int c, int l)
{
	char *cm_cap;

	cm_cap = tgetstr("cm", NULL);
	tputs(tgoto(cm_cap, c, l), 1, ft_putchar2);
}

void	scroll_n_times(int n)
{
	char *sf_cap;

	sf_cap = tgetstr("sf", NULL);
	while (n)
	{
		tputs(sf_cap, 1, ft_putchar2);
		n--;
	}
}

void	clear_after_cursor(void)
{
	char *cd_cap;

	cd_cap = tgetstr("cd", NULL);
	tputs(cd_cap, 1, ft_putchar2);
}

void	print_at_cursor(char c)
{
	ft_putchar_fd(c, STDIN_FILENO);
	if (tcaps.c_pos + 1 < tcaps.c_max)
		move_cursor(tcaps.c_pos + 1, tcaps.l_pos);
	else if (tcaps.c_pos + 1 == tcaps.c_max && tcaps.l_pos + 1 != tcaps.l_max)
	{
		move_cursor(0, tcaps.l_pos + 1);
		tcaps.line_lvl++;
		tcaps.cursor_lvl++;
	}
	else if (tcaps.c_pos + 1 == tcaps.c_max && tcaps.l_pos + 1 == tcaps.l_max)
	{
		scroll_n_times(1);
		move_cursor(0, tcaps.l_pos + 1);
		tcaps.line_lvl++;
		tcaps.cursor_lvl++;
	}
	cursor_position();
	tcaps.cursor_max = tcaps.c_pos;
}

void	backspace(int *i, char **line)
{
	char *oldline;
	char *dc_cap;

	oldline = *line;
	if (*i > 0)
		(*i)--;
	*line = ft_substr(oldline, 0, *i);
	free(oldline);
	dc_cap = tgetstr("dc", NULL);
	if ((tcaps.c_pos - 1 >= tcaps.c_start && !tcaps.line_lvl) || (tcaps.c_pos - 1 >= 0 && tcaps.line_lvl))
	{
		move_cursor(tcaps.c_pos - 1, tcaps.l_pos);
		tputs(dc_cap, 1, ft_putchar2);
		tcaps.cursor_max--;
	}
	else if (tcaps.c_pos - 1 < 0 && tcaps.line_lvl)
	{
		move_cursor(tcaps.c_max - 1, tcaps.l_pos - 1);
		tputs(tgetstr("ce", NULL), 1, ft_putchar2);
		tcaps.line_lvl--;
		tcaps.cursor_lvl--;
		tcaps.cursor_max = tcaps.c_max - 1;
	}
	tcaps.cursor_pos = *i;
}

void	history_older(int *i, char **line, t_big *datas, int flag)
{
	char *cd_cap;

	cd_cap = tgetstr("cd", NULL);
	while (tcaps.cursor_lvl)
	{
		move_cursor(0, tcaps.l_pos--);
		tcaps.cursor_lvl--;
	}
	move_cursor(tcaps.c_start, tcaps.l_pos);
	tputs(cd_cap, tcaps.l_max - tcaps.l_pos, ft_putchar2);
	browse_history(datas, line, flag);
	*i = ft_strlen(*line);
	tcaps.cursor_pos = *i;
	cursor_position();
	tcaps.cursor_max = tcaps.c_pos;
}

void	clear_term(void)
{
	int		cursor_flag;
	int		decrement;

	cursor_flag = 0;
	cursor_position();
	if (tcaps.l_max - 1 <= tcaps.cursor_lvl)
		return ;
	decrement = tcaps.l_max - 1 - tcaps.cursor_lvl;
	if (decrement)
	{
		cursor_flag = 1;
		scroll_n_times(decrement);
	}
	if (cursor_flag)
		move_cursor(tcaps.c_pos, tcaps.cursor_lvl);
}

void	move_cursor_left(void)
{
	if ((tcaps.c_pos - 1 >= tcaps.c_start && !tcaps.cursor_lvl) || (tcaps.c_pos - 1 >= 0 && tcaps.cursor_lvl))
	{
		move_cursor(tcaps.c_pos - 1, tcaps.l_pos);
		tcaps.cursor_pos--;
	}
	else if (tcaps.c_pos - 1 < 0 && tcaps.cursor_lvl)
	{
		move_cursor(tcaps.c_max - 1, tcaps.l_pos - 1);
		tcaps.cursor_lvl--;
		tcaps.cursor_pos--;
	}
}

void	move_cursor_right(void)
{
	if (tcaps.cursor_lvl == tcaps.line_lvl)
	{
		if (tcaps.c_pos + 1 <= tcaps.cursor_max)
		{
			move_cursor(tcaps.c_pos + 1, tcaps.l_pos);
			tcaps.cursor_pos++;
		}
	}
	else if (tcaps.cursor_lvl < tcaps.line_lvl)
	{
		if (tcaps.c_pos + 1 < tcaps.c_max)
			move_cursor(tcaps.c_pos + 1, tcaps.l_pos);
		else
		{
			move_cursor(0, tcaps.l_pos + 1);
			tcaps.cursor_lvl++;
		}
		tcaps.cursor_pos++;
	}
}

void	backspace_at_cursor(int *i, char **line)
{
	char	*oldline;
	char	*tmp;
	int		c_next = 0;
	int		l_next = 0;

	oldline = *line;
	*line = ft_substr(oldline, 0, tcaps.cursor_pos - 1);
	tmp = ft_substr(oldline, tcaps.cursor_pos, *i);
	free(oldline);
	*line = ft_realloc(*line, ft_strlen(*line) + ft_strlen(tmp) + 1);
	ft_strlcat(*line, tmp, ft_strlen(*line) + ft_strlen(tmp) + 1);
	if (*i > 0)
		(*i)--;
	lines_added(*line);
	if ((tcaps.c_pos - 1 >= tcaps.c_start && !tcaps.cursor_lvl) || (tcaps.c_pos - 1 >= 0 && tcaps.cursor_lvl))
	{
		c_next = tcaps.c_pos - 1;
		l_next = tcaps.l_pos;
		tcaps.cursor_pos--;
		move_cursor(tcaps.c_start, tcaps.l_pos - tcaps.cursor_lvl);
	}
	else if (tcaps.c_pos - 1 < 0 && tcaps.cursor_lvl)
	{
		c_next = tcaps.c_max - 1;
		l_next = tcaps.l_pos - 1;
		tcaps.cursor_pos--;
		move_cursor(tcaps.c_start, tcaps.l_pos - tcaps.cursor_lvl);
		tcaps.cursor_lvl--;
	}
	clear_after_cursor();
	ft_putstr_fd(*line, STDIN_FILENO);
	cursor_position();
	tcaps.cursor_max = tcaps.c_pos;
	move_cursor(c_next, l_next);
}

void 	add_at_cursor(char c, int *i, char **line)
{
	char *oldline;
	char *tmp;
	int c_next = 0;
	int l_next = 0;

	oldline = *line;
	*line = ft_substr(oldline, 0, tcaps.cursor_pos);
	tmp = ft_substr(oldline, tcaps.cursor_pos, *i);
	free(oldline);
	*line = ft_realloc(*line, ft_strlen(*line) + 1 + ft_strlen(tmp) + 1);
	(*line)[tcaps.cursor_pos] = c;
	(*line)[tcaps.cursor_pos + 1] = 0;
	ft_strlcat(*line, tmp, ft_strlen(*line) + ft_strlen(tmp) + 1);
	(*i)++;
	lines_added(*line);
	clear_after_cursor();
	if (tcaps.c_pos + 1 < tcaps.c_max)
	{
		c_next = tcaps.c_pos + 1;
		l_next = tcaps.l_pos;
		tcaps.cursor_pos++;
	}
	else if (tcaps.c_pos + 1 == tcaps.c_max && tcaps.l_pos + 1 < tcaps.l_max)
	{
		c_next = 0;
		l_next = tcaps.l_pos + 1;
		tcaps.cursor_lvl++;
		tcaps.cursor_pos++;
	}
	ft_putchar_fd(c, STDIN_FILENO);
	ft_putstr_fd(tmp, STDIN_FILENO);
	cursor_position();
	tcaps.cursor_max = tcaps.c_pos;
	move_cursor(c_next, l_next);
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
	term_size();
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
		end_of_transmission(datas, *line);
	else if (buf[0] > 31 && buf[0] < 127)
		add_at_cursor(buf[0], i, line);
	else if	(buf[0] == 27 && buf[1] == 91 && buf[2] == 72)
		go_home();
	else if(buf[0] == 27 && buf[1]== 91 && buf[2] == 70)
		go_end(i);
}
