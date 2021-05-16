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

char	*backspace_line_edition(int *i, char **line)
{
	char *oldline;

	oldline = *line;
	if (*i > 0)
		(*i)--;
	*line = ft_substr(oldline, 0, *i);
	if (oldline)
		free(oldline);
	return (*line);
}

int	backspace(int *i, char **line)
{
	int		ret;
	char 	*dc_cap;
	char 	*ce_cap;

	*line = backspace_line_edition(i, line);
	dc_cap = tgetstr("dc", NULL);
	ce_cap = tgetstr("ce", NULL);
	if (!(*line) || !dc_cap || !ce_cap)
		return(printi_stderr(0, strerror(errno), 0));
	if ((tcaps.c_pos - 1 >= tcaps.c_start && !tcaps.line_lvl) || \
	(tcaps.c_pos - 1 >= 0 && tcaps.line_lvl))
	{
		ret = move_cursor(tcaps.c_pos - 1, tcaps.l_pos);
		if (!ret)
			return (ERROR);
		ret = tputs(dc_cap, 1, ft_putchar2);
		if (ret == ERR)
			return (printi_stderr(0, "tputs failed in ft_backspace\n", 0));
		tcaps.cursor_max--;
	}
	else if (tcaps.c_pos - 1 < 0 && tcaps.line_lvl)
	{
		ret = move_cursor(tcaps.c_max - 1, tcaps.l_pos - 1);
		if (!ret)
			return (ERROR);
		ret = tputs(ce_cap, 1, ft_putchar2);
		if (ret == ERR)
			return (printi_stderr(0, "tputs failed in ft_backspace\n", 0));
		tcaps.line_lvl--;
		tcaps.cursor_lvl--;
		tcaps.cursor_max = tcaps.c_max - 1;
	}
	tcaps.cursor_pos = *i;
	return (1);
}

char	*backspace_middleline_edition(int *i, char **line)
{
	char	*oldline;
	char	*tmp;

	oldline = *line;
	*line = ft_substr(oldline, 0, tcaps.cursor_pos - 1);
	tmp = ft_substr(oldline, tcaps.cursor_pos, *i);
	if (!tmp || !(*line))
	{
		clean_free(&tmp);
		clean_free(&oldline);
		clean_free(line);
		return (printc_stderr(0, strerror(errno), 0));
	}
	if (oldline)
		free(oldline);
	*line = ft_realloc(*line, ft_strlen(*line) + ft_strlen(tmp) + 1);
	if (!(*line))
	{
		clean_free(&tmp);
		return (printc_stderr(0, strerror(errno), 0));
	}
	ft_strlcat(*line, tmp, ft_strlen(*line) + ft_strlen(tmp) + 1);
	if (*i > 0)
		(*i)--;
	lines_added(*line);
	if (tmp)
		free(tmp);
	return (*line);
}

int		print_and_get_max(char **line)
{
	ft_putstr_fd(*line, STDIN_FILENO);
	return (get_cursor_max());
}

int		backspace_at_cursor(int *i, char **line)
{
	int	ret;
	int	c_next;
	int	l_next;

	ret = 1;
	c_next = 0;
	l_next = 0;
	*line = backspace_middleline_edition(i, line);
	if (!(*line))
		return(printi_stderr(0, strerror(errno), 0));
	if ((tcaps.c_pos - 1 >= tcaps.c_start && !tcaps.cursor_lvl) || \
	(tcaps.c_pos - 1 >= 0 && tcaps.cursor_lvl))
	{
		c_next = tcaps.c_pos - 1;
		l_next = tcaps.l_pos;
		tcaps.cursor_pos--;
		ret = move_cursor(tcaps.c_start, tcaps.l_pos - tcaps.cursor_lvl);
	}
	else if (tcaps.c_pos - 1 < 0 && tcaps.cursor_lvl)
	{
		c_next = tcaps.c_max - 1;
		l_next = tcaps.l_pos - 1;
		tcaps.cursor_pos--;
		ret = move_cursor(tcaps.c_start, tcaps.l_pos - tcaps.cursor_lvl);
		tcaps.cursor_lvl--;
	}
	if (!ret)
		return (ERROR);
	ret = clear_after_cursor();
	if (!ret)
		return (ERROR);
	ret = print_and_get_max(line);
	if (!ret)
		return (ERROR);
	ret = move_cursor(c_next, l_next);
	return (ret);
}
