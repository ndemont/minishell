/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 10:13:41 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/06 12:17:17 by ndemont          ###   ########.fr       */
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

int		termcaps_init(void)
{
	int		ret;
	char	*term;

	term = getenv("TERM");
	if (!term || (ret = tgetent(NULL, term)) <= 0)
		return (0);
	return (1);
}

int	term_size(void)
{
	int				ret;
	struct winsize	w;

	ret = ioctl(0, TIOCGWINSZ, &w);
	if (ret < 0)
		return(printi_stderr(0, strerror(errno), 0));
	tcaps.l_max = w.ws_row;
	tcaps.c_max = w.ws_col;
	return (1);
}

int		ft_putchar2(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
