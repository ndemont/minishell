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

int	raw_mode(void)
{
	int	ret;

	ret = tcgetattr(STDIN_FILENO, &g_tcaps.save);
	if (ret == ERR)
		return (printi_stderr(0, strerror(errno), 0));
	g_tcaps.term = g_tcaps.save;
	g_tcaps.term.c_lflag &= ~(ECHO | ICANON);
	ret = tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_tcaps.term);
	if (ret == ERR)
		return (printi_stderr(0, strerror(errno), 0));
	return (SUCCESS);
}

int	normal_mode(void)
{
	int	ret;

	ret = tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_tcaps.save);
	if (ret == ERR)
		return (printi_stderr(0, strerror(errno), 0));
	return (SUCCESS);
}

int	termcaps_init(void)
{
	int		ret;
	char	*term;

	term = getenv("TERM");
	if (!term)
		return (printi_stderr(0, "TC init did fail.\n", 0));
	ret = tgetent(NULL, term);
	if (ret == ERR)
		return (printi_stderr(0, "TC init did fail.\n", 0));
	return (SUCCESS);
}

int	term_size(void)
{
	int				ret;
	struct winsize	w;

	ret = ioctl(0, TIOCGWINSZ, &w);
	if (ret < 0)
		return (printi_stderr(0, strerror(errno), 0));
	g_tcaps.l_max = w.ws_row;
	g_tcaps.c_max = w.ws_col;
	return (SUCCESS);
}

int	ft_putchar2(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
