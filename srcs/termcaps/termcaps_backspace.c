/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_backspace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 10:22:24 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/03 10:22:34 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backspace_line_edition(int *i, char **line)
{
	char *oldline;

	oldline = *line;
	if (*i > 0)
		(*i)--;
	*line = ft_substr(oldline, 0, *i);
	if (oldline)
		free(oldline);
}

void	backspace(int *i, char **line)
{
	char *dc_cap;
	char *ce_cap;

	backspace_line_edition(i, line);
	dc_cap = tgetstr("dc", NULL);
	ce_cap = tgetstr("ce", NULL);
	if (!dc_cap || !ce_cap)
		exit(0);
	if ((tcaps.c_pos - 1 >= tcaps.c_start && !tcaps.line_lvl) || \
	(tcaps.c_pos - 1 >= 0 && tcaps.line_lvl))
	{
		move_cursor(tcaps.c_pos - 1, tcaps.l_pos);
		tputs(dc_cap, 1, ft_putchar2);
		tcaps.cursor_max--;
	}
	else if (tcaps.c_pos - 1 < 0 && tcaps.line_lvl)
	{
		move_cursor(tcaps.c_max - 1, tcaps.l_pos - 1);
		tputs(ce_cap, 1, ft_putchar2);
		tcaps.line_lvl--;
		tcaps.cursor_lvl--;
		tcaps.cursor_max = tcaps.c_max - 1;
	}
	tcaps.cursor_pos = *i;
}

void	backspace_middleline_edition(int *i, char **line)
{
	char	*oldline;
	char	*tmp;

	oldline = *line;
	*line = ft_substr(oldline, 0, tcaps.cursor_pos - 1);
	tmp = ft_substr(oldline, tcaps.cursor_pos, *i);
	if (oldline)
		free(oldline);
	*line = ft_realloc(*line, ft_strlen(*line) + ft_strlen(tmp) + 1);
	ft_strlcat(*line, tmp, ft_strlen(*line) + ft_strlen(tmp) + 1);
	if (*i > 0)
		(*i)--;
	lines_added(*line);
	if (tmp)
		free(tmp);
}

void	print_and_get_max(char **line)
{
	ft_putstr_fd(*line, STDIN_FILENO);
	get_cursor_max();
}

void	backspace_at_cursor(int *i, char **line)
{
	int		c_next;
	int		l_next;

	c_next = 0;
	l_next = 0;
	backspace_middleline_edition(i, line);
	if ((tcaps.c_pos - 1 >= tcaps.c_start && !tcaps.cursor_lvl) || \
	(tcaps.c_pos - 1 >= 0 && tcaps.cursor_lvl))
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
	print_and_get_max(line);
	move_cursor(c_next, l_next);
}
