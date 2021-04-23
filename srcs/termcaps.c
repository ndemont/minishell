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
	tcaps.c_max = tgetnum("co");
	tcaps.l_max = tgetnum("li");
	//printf("C_MAX = [%i]\n", tcaps.c_max);
	//printf("L_MAX = [%i]\n", tcaps.l_max);
	write(1, "\033[6n", 4);
	read(1, buf, 100);
	printf("%s", buf);
}