/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 13:46:13 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/28 23:38:49 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_line_edition(int *i, char **line)
{
	char *oldline;
	char *tmp;

	oldline = *line;
	*line = ft_substr(oldline, 0, tcaps.cursor_pos);
	tmp = ft_substr(oldline, tcaps.cursor_pos + 1, *i);
	if (oldline)
		free(oldline);
	if (!(*line) || !tmp)
	{
		clean_free(line);
		clean_free(&tmp);
		return (printc_stderr(0, strerror(errno), 0));
	}
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
	return (tmp);
}

int	delete_at_cursor(int *i, char **line)
{
	char	ret;
	char	*tmp;
	int		c_pos;
	int		l_pos;

	tmp = delete_line_edition(i, line);
	if (!tmp)
		return (ERROR);
	ret = clear_after_cursor();
	if (!ret)
	{
		clean_free(&tmp);
		return (ERROR);
	}
	ret = cursor_position();
	if (!ret)
	{
		clean_free(&tmp);
		return (ERROR);
	}
	c_pos = tcaps.c_pos;
	l_pos = tcaps.l_pos;
	ft_putstr_fd(tmp, STDIN_FILENO);
	clean_free(&tmp);
	ret = get_cursor_max();
	if (!ret)
		return (ERROR);
	return (move_cursor(c_pos, l_pos));
}

int	ctrl_d(t_big *datas, char **line, int *i)
{
	if (*line && !(*line)[0])
	{
		clean_free(line);
		write(0, "exit\n", 5);
		update_history_file(datas);
		//free_tokens(token_tab);
		free_datas(datas);
		exit(1);
	}
	else if (*line && (*line)[0] && tcaps.cursor_pos < *i)
		return (delete_at_cursor(i, line));
	return (SUCCESS);
}
