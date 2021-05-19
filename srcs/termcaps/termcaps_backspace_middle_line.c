/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_backspace_middle_line.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 18:51:35 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/16 18:51:36 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*backspace_middleline_edition(int *i, char **line)
{
	char	*oldline;
	char	*tmp;

	oldline = *line;
	*line = ft_substr(oldline, 0, g_tcaps.cursor_pos - 1);
	tmp = ft_substr(oldline, g_tcaps.cursor_pos, *i);
	if (!tmp || !(*line))
	{
		clean_the_mess(&tmp, &oldline, line);
		return (printc_stderr(0, strerror(errno), 0));
	}
	clean_free(&oldline);
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

int	print_and_get_max(char **line)
{
	ft_putstr_fd(*line, STDIN_FILENO);
	return (get_cursor_max());
}

int	at_cursor_first_case(int *c_next, int *l_next)
{
	*c_next = g_tcaps.c_pos - 1;
	*l_next = g_tcaps.l_pos;
	g_tcaps.cursor_pos--;
	return (move_cursor(g_tcaps.c_start, g_tcaps.l_pos - g_tcaps.cursor_lvl));
}

int	at_cursor_second_case(int *c_next, int *l_next)
{
	int	ret;

	*c_next = g_tcaps.c_max - 1;
	*l_next = g_tcaps.l_pos - 1;
	g_tcaps.cursor_pos--;
	ret = move_cursor(g_tcaps.c_start, g_tcaps.l_pos - g_tcaps.cursor_lvl);
	g_tcaps.cursor_lvl--;
	return (ret);
}

int	backspace_at_cursor(int *i, char **line)
{
	int	ret;
	int	c_next;
	int	l_next;

	ret = 1;
	c_next = 0;
	l_next = 0;
	*line = backspace_middleline_edition(i, line);
	if (!(*line))
		return (ERROR);
	if ((g_tcaps.c_pos - 1 >= g_tcaps.c_start && !g_tcaps.cursor_lvl) || \
	(g_tcaps.c_pos - 1 >= 0 && g_tcaps.cursor_lvl))
		ret = at_cursor_first_case(&c_next, &l_next);
	else if (g_tcaps.c_pos - 1 < 0 && g_tcaps.cursor_lvl)
		ret = at_cursor_second_case(&c_next, &l_next);
	if (!ret)
		return (ERROR);
	ret = clear_after_cursor();
	if (!ret)
		return (ERROR);
	ret = print_and_get_max(line);
	if (!ret)
		return (ERROR);
	return (move_cursor(c_next, l_next));
}
