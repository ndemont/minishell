/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_add_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 10:25:44 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/03 10:25:47 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_line_edition(char c, int *i, char **line)
{
	char	*oldline;
	char	*tmp;

	oldline = *line;
	*line = ft_substr(oldline, 0, g_tcaps.cursor_pos);
	tmp = ft_substr(oldline, g_tcaps.cursor_pos, *i);
	clean_free(&oldline);
	if (!(*line) || !tmp)
	{
		clean_free(&tmp);
		clean_free(line);
		return (printc_stderr(0, strerror(errno), 0));
	}
	*line = ft_realloc(*line, ft_strlen(*line) + 1 + ft_strlen(tmp) + 1);
	if (!(*line))
	{
		clean_free(&tmp);
		return (printc_stderr(0, strerror(errno), 0));
	}
	(*line)[g_tcaps.cursor_pos] = c;
	(*line)[g_tcaps.cursor_pos + 1] = 0;
	ft_strlcat(*line, tmp, ft_strlen(*line) + ft_strlen(tmp) + 1);
	(*i)++;
	lines_added(*line);
	return (tmp);
}

int	do_some_things(int *c_next, int *l_next)
{
	int	ret;

	ret = clear_after_cursor();
	if (!ret)
		return (ERROR);
	if (g_tcaps.c_pos + 1 < g_tcaps.c_max)
	{
		*c_next = g_tcaps.c_pos + 1;
		*l_next = g_tcaps.l_pos;
		g_tcaps.cursor_pos++;
	}
	else if (g_tcaps.c_pos + 1 == g_tcaps.c_max && \
	g_tcaps.l_pos + 1 < g_tcaps.l_max)
	{
		*c_next = 0;
		*l_next = g_tcaps.l_pos + 1;
		g_tcaps.cursor_lvl++;
		g_tcaps.cursor_pos++;
	}
	return (SUCCESS);
}

void	print_new_char(char c, char **tmp)
{
	ft_putchar_fd(c, STDIN_FILENO);
	ft_putstr_fd(*tmp, STDIN_FILENO);
	clean_free(tmp);
}

int	add_at_cursor(char c, int *i, char **line)
{
	int		ret;
	int		c_next;
	int		l_next;
	int		old_line_lvl;
	char	*tmp;

	c_next = 0;
	l_next = 0;
	old_line_lvl = g_tcaps.line_lvl;
	tmp = add_line_edition(c, i, line);
	if (!tmp)
		return (ERROR);
	ret = do_some_things(&c_next, &l_next);
	if (!ret)
	{
		clean_free(&tmp);
		return (ERROR);
	}
	print_new_char(c, &tmp);
	ret = get_cursor_max();
	if (!ret)
		return (ERROR);
	if (g_tcaps.line_lvl > old_line_lvl && g_tcaps.l_pos + 1 == g_tcaps.l_max)
		l_next--;
	return (move_cursor(c_next, l_next));
}

int	print_at_cursor(char c)
{
	int	ret;

	ret = SUCCESS;
	ft_putchar_fd(c, STDIN_FILENO);
	if (g_tcaps.c_pos + 1 < g_tcaps.c_max)
		ret = move_cursor(g_tcaps.c_pos + 1, g_tcaps.l_pos);
	else if (g_tcaps.c_pos + 1 == g_tcaps.c_max && \
	g_tcaps.l_pos + 1 != g_tcaps.l_max)
	{
		ret = move_cursor(0, g_tcaps.l_pos + 1);
		g_tcaps.line_lvl++;
		g_tcaps.cursor_lvl++;
	}
	else if (g_tcaps.c_pos + 1 == g_tcaps.c_max && \
	g_tcaps.l_pos + 1 == g_tcaps.l_max)
	{
		ret = scroll_n_times(1);
		if (!ret)
			return (ERROR);
		ret = move_cursor(0, g_tcaps.l_pos);
		g_tcaps.line_lvl++;
		g_tcaps.cursor_lvl++;
	}
	g_tcaps.cursor_max = g_tcaps.c_pos;
	return (ret);
}
