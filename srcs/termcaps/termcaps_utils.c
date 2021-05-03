/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 10:13:41 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/03 10:13:43 by gpetit           ###   ########.fr       */
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
	if (!term || (ret = tgetent(NULL, term)) <= 0)
		exit(0); // changer methode d'exit
}

void	term_size(void)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
    tcaps.l_max = w.ws_row;
    tcaps.c_max = w.ws_col;
}

int		ft_putchar2(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}