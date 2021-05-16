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
	*line = ft_substr(oldline, 0, tcaps.cursor_pos);
	tmp = ft_substr(oldline, tcaps.cursor_pos, *i);
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
	(*line)[tcaps.cursor_pos] = c;
	(*line)[tcaps.cursor_pos + 1] = 0;
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
	if (tcaps.c_pos + 1 < tcaps.c_max)
	{
		*c_next = tcaps.c_pos + 1;
		*l_next = tcaps.l_pos;
		tcaps.cursor_pos++;
	}
	else if (tcaps.c_pos + 1 == tcaps.c_max && tcaps.l_pos + 1 < tcaps.l_max)
	{
		*c_next = 0;
		*l_next = tcaps.l_pos + 1;
		tcaps.cursor_lvl++;
		tcaps.cursor_pos++;
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
	old_line_lvl = tcaps.line_lvl;
	tmp = add_line_edition(c, i, line);
	if (!tmp)
		return (ERROR);
	ret = do_some_things(&c_next, &l_next);
	if (!ret)
	{
		clean_free(&tmp);
		return (ERROR);
	}
	print_at_cursor(c, &tmp);
	ret = get_cursor_max();
	if (!ret)
		return (ERROR);
	if (tcaps.line_lvl > old_line_lvl && tcaps.l_pos + 1 == tcaps.l_max)
		l_next--;
	return (move_cursor(c_next, l_next));
}

void	print_at_cursor(char c)
{
	ft_putchar_fd(c, STDIN_FILENO);
	if (tcaps.c_pos + 1 < tcaps.c_max)
		move_cursor(tcaps.c_pos + 1, tcaps.l_pos);
	else if (tcaps.c_pos + 1 == tcaps.c_max && tcaps.l_pos + 1 != tcaps.l_max)
	{
		move_cursor(0, tcaps.l_pos + 1);
		tcaps.line_lvl++;
		tcaps.cursor_lvl++;
	}
	else if (tcaps.c_pos + 1 == tcaps.c_max && tcaps.l_pos + 1 == tcaps.l_max)
	{
		scroll_n_times(1);
		move_cursor(0, tcaps.l_pos);
		tcaps.line_lvl++;
		tcaps.cursor_lvl++;
	}
	tcaps.cursor_max = tcaps.c_pos;
}
