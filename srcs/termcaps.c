/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:51:10 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/26 12:17:46 by ndemont          ###   ########.fr       */
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

void	DEVELOPMENT_MODE_print_sequence(char *buf)
{
	int fd = open("input_sequence", O_CREAT | O_APPEND | O_WRONLY, 0644);
	int i = 0;
	while(buf[i])
		dprintf(fd, "[%d] ", (int)buf[i++]);
	dprintf(fd, "||");
	//dprintf(fd, "[%s]\n", buf);
	close(fd);
}

void	DEVELOPMENT_MODE_print_termcaps(void)
{
	int fd = open("termcaps", O_CREAT | O_APPEND | O_WRONLY, 0644);
	dprintf(fd, "Prompt Line = %i\n", tcaps.l_prompt);
	dprintf(fd, "Max Column = %i\n", tcaps.c_max);
	dprintf(fd, "Max Line = %i\n", tcaps.l_max);
	dprintf(fd, "Current_Column_position = %i\n", tcaps.c_pos);
	dprintf(fd, "Current_Line_position = %i\n", tcaps.l_pos);
	dprintf(fd, "Start = %i\n", tcaps.c_start);
	dprintf(fd, "line_depth = %i\n", tcaps.line_lvl);
	dprintf(fd, "<===============================>\n");
	close(fd);
}

void	termcaps_init(void)
{
	int ret;
	char *term;

	term = getenv("TERM");

	if ((ret = tgetent(NULL, term)) <= 0)
		exit(0); // changer methode d'exit
}

void	cursor_position(void)
{
	char buf[100];
	int i;

	tcaps.c_max = tgetnum("co");
	tcaps.l_max = tgetnum("li");
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

void	print_at_cursor(char c)
{
/* 	char *im_cap;
	char *ic_cap; */
	char *cm_cap;

	/* im_cap = tgetstr("im", NULL);
	tputs(im_cap, STDIN_FILENO, ft_putchar2);
	ic_cap = tgetstr("ic", NULL);
	tputs(ic_cap, STDIN_FILENO, ft_putchar2); */
	
	write(STDIN_FILENO, &c, 1);
	cm_cap = tgetstr("cm", NULL);
	if (tcaps.c_pos + 1 < tcaps.c_max)
		tputs(tgoto(cm_cap, tcaps.c_pos + 1, tcaps.l_pos), STDIN_FILENO, ft_putchar2);
	else
	{
		tputs(tgoto(cm_cap, 0, tcaps.l_pos + 1), STDIN_FILENO, ft_putchar2);
		tcaps.line_lvl++;
		//DEVELOPMENT_MODE_print_sequence(ft_itoa(tcaps.line_lvl));
	}
}

void	backspace(int *i, char **line)
{
	char *oldline;
	char *cm_cap;
	char *dc_cap;

	oldline = *line;
	if (*i > 0)
		(*i)--;
	*line = ft_substr(oldline, 0, *i);
	free(oldline);
	cm_cap = tgetstr("cm", NULL);
	dc_cap = tgetstr("dc", NULL);
	if ((tcaps.c_pos - 1 >= tcaps.c_start && !tcaps.line_lvl) || (tcaps.c_pos - 1 >= 0 && tcaps.line_lvl))
	{
		tputs(tgoto(cm_cap, tcaps.c_pos - 1, tcaps.l_pos), 1, ft_putchar2);
		tputs(dc_cap, 1, ft_putchar2);
	}
	else if (tcaps.c_pos - 1 < 0 && tcaps.line_lvl)
	{
		//DEVELOPMENT_MODE_print_termcaps();
		tputs(tgoto(cm_cap, tcaps.c_max - 1, tcaps.l_pos - 1), 2, ft_putchar2);
		tputs(tgetstr("cd", NULL), tcaps.l_max - tcaps.l_pos, ft_putchar2); //WORKING !!!!!
		//tputs(dc_cap, tcaps.c_max - tcaps.c_pos, ft_putchar2); //NOT WORKING
		tcaps.line_lvl--;
		cursor_position();
	}
}

void	history_older(int *i, char **line, t_big *datas, int flag)
{
	char *ce_cap;
	char *cm_cap;

	cm_cap = tgetstr("cm", NULL);
	ce_cap = tgetstr("ce", NULL);
	while (tcaps.line_lvl)
	{	
		tputs(tgoto(cm_cap, 0, tcaps.l_pos--), 1, ft_putchar2);
		tputs(ce_cap, 1, ft_putchar2);
		tcaps.line_lvl--;
	}
	tputs(tgoto(cm_cap, tcaps.c_start, tcaps.l_pos), 1, ft_putchar2);
	tputs(ce_cap, 1, ft_putchar2);
	browse_history(datas, line, flag);
	*i = ft_strlen(*line);
}

void	do_the_right_thing(int *i, char *buf, char **line, t_big *datas)
{
	if(buf[0] == 127)
		backspace(i, line);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		history_older(i, line, datas, 1);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		history_older(i, line, datas, 0);
}
