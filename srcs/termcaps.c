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
	tcaps.c_max = tgetnum("co");
	tcaps.l_max = tgetnum("li");
	//printf("C_MAX = [%i]\n", tcaps.c_max);
	//printf("L_MAX = [%i]\n", tcaps.l_max);
	write(STDOUT_FILENO, "\033[6n", 4);
}