/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:51:10 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/22 18:06:22 by gpetit           ###   ########.fr       */
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

void	DEVELOPPMENT_MODE_print_sequence(char *buf)
{
	int fd = open("input_sequence", O_CREAT | O_APPEND | O_WRONLY, 0644);
	int i = 0;
	while(buf[i])
		dprintf(fd, "[%d] ", (int)buf[i++]);
	dprintf(fd, "||");
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
	//printf("C_MAX = [%i]\n", tcaps.c_max);
	//printf("L_MAX = [%i]\n", tcaps.l_max);
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

	//UtiLE POUR CONTROLER SANS POURRIR LE STDOUT
	/* int fd = open("CURSOR_POS", O_CREAT | O_APPEND | O_WRONLY, 0644);
	dprintf(fd, "%s", buf);
	dprintf(fd, "C_POS = [%i]\n", tcaps.c_pos);
	dprintf(fd, "L_POS = [%i]\n", tcaps.l_pos);
	dprintf(fd, "\n");
	close(fd); */
}

int		ft_putchar2(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void	backspace(int *i, char **line)
{
	char *oldline;
	char *cm_cap;
	char *dc_cap;

	oldline = *line;
	if (*i > 0)
		*i -= 1;
	*line = ft_substr(oldline, 0, *i);
	free(oldline);
	cm_cap = tgetstr("cm", NULL);
	if (tcaps.c_pos - 1 >= tcaps.c_start)
	{
		tputs(tgoto(cm_cap, tcaps.c_pos - 1, tcaps.l_pos), STDIN_FILENO, ft_putchar2);
		dc_cap = tgetstr("dc", NULL);
		tputs(dc_cap, STDIN_FILENO, ft_putchar2);
	}
}

void	do_the_right_thing(int *i, char *buf, char **line)
{
	if(buf[0] == 127)
		backspace(i, line);
}