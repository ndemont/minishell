/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_creation_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:25:16 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/26 11:07:45 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_line(int *i, char **line, char *buf)
{
	*line = ft_realloc(*line, ft_strlen(*line) + 2);
	if (!(*line))
		return (printi_stderr(0, strerror(errno), 0));
	ft_strlcat(*line, buf, ft_strlen(*line) + 2);
	(*line)[*i] = 0;
	return (SUCCESS);
}

void	check_if_non_print(char *buf, int *non_print_flag, t_big *datas)
{
	int	j;

	j = 0;
	(void)datas;
	while (buf[j])
	{
		if ((int)buf[j] == 10)
			break ;
		else if (((int)buf[j] >= 0 && (int)buf[j] <= 31) || (int)buf[j] == 127)
			*non_print_flag = 1;
		j++;
	}
}

int	launch_termcaps(char *buf, char **line, int *i, t_big *datas)
{
	int	ret;
	int	level;

	level = g_tcaps.l_pos + (g_tcaps.line_lvl - g_tcaps.cursor_lvl);
	if (buf[0] == 10)
	{
		ret = execute_line(i, line, buf);
		if (!ret)
			return (ERROR);
		else
		{
			move_cursor(g_tcaps.cursor_max, level);
			return (BREAK_LOOP);
		}
	}
	ret = do_the_right_thing(i, buf, line, datas);
	return (ret);
}

int	edit_and_print_line(char *buf, char **line, int *i, t_big *datas)
{
	int	ret;

	*line = ft_realloc(*line, ft_strlen(*line) + 1 + 1);
	if (!(*line))
		return (printi_stderr(0, strerror(errno), 0));
	ft_strlcat(*line, buf, ft_strlen(*line) + 2);
	if (buf[0] != '\n')
	{
		(*line)[*i] = buf[0];
		(*line)[*i + 1] = 0;
	}
	else
	{
		(*line)[*i] = 0;
		return (BREAK_LOOP);
	}
	ret = print_at_cursor((*line)[*i]);
	if (!ret)
		return (ERROR);
	(*i)++;
	g_tcaps.cursor_pos = *i;
	datas->flag_history = 0;
	return (SUCCESS);
}
