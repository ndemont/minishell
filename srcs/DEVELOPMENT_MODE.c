/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DEVELOPMENT_MODE.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:33:05 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/27 10:33:08 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	DEVELOPMENT_MODE_print_str(char *buf)
{
	int fd = open("DEBUG_str", O_CREAT | O_APPEND | O_WRONLY, 0644);
	dprintf(fd, "str = [%s] || line_level = [%i]\n", buf, tcaps.line_lvl);
	close(fd);
}

void	DEVELOPMENT_MODE_print_sequence(char *buf)
{
	int fd = open("DEBUG_sequence", O_CREAT | O_APPEND | O_WRONLY, 0644);
	int i = 0;
	while(buf[i])
		dprintf(fd, "[%d] ", (int)buf[i++]);
	dprintf(fd, "||");
	//dprintf(fd, "[%s]\n", buf);
	close(fd);
}

void	DEVELOPMENT_MODE_print_nbr(long n)
{
	int fd = open("DEBUG_NBR", O_CREAT | O_APPEND | O_WRONLY, 0644);

	ft_putnbr_fd(n, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}


void	DEVELOPMENT_MODE_print_termcaps(char *str)
{
	int fd = open("DEBUG_termcaps", O_CREAT | O_APPEND | O_WRONLY, 0644);

	cursor_position();
	dprintf(fd, "%s\n\n", str);
	dprintf(fd, "Max Column = %i\n", tcaps.c_max);
	dprintf(fd, "Max Line = %i\n", tcaps.l_max);
	dprintf(fd, "Current_Column_position = %i\n", tcaps.c_pos);
	dprintf(fd, "Current_Line_position = %i\n", tcaps.l_pos);
	dprintf(fd, "Start = %i\n", tcaps.c_start);
	dprintf(fd, "line_depth = %i\n", tcaps.line_lvl);
	dprintf(fd, "<===============================>\n");
	close(fd);
}
