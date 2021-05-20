/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:21:59 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/20 16:22:00 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	interpret_signal(char **line, int *i)
{
	if (g_tcaps.signal)
	{
		clean_free(line);
		*line = ft_strdup("");
		if (!(*line))
			return (printi_stderr(0, strerror(errno), 0));
		g_tcaps.signal = 0;
		*i = 0;
	}
	return (SUCCESS);
}

int	initiate_line_buffer(char *buf, int *non_print_flag)
{
	int	ret;

	*non_print_flag = 0;
	ft_bzero(buf, 7);
	ret = read(STDIN_FILENO, buf, 6);
	if (ret == ERR)
		return (printi_stderr(0, strerror(errno), 0));
	else if (ret == 0)
		return (BREAK_LOOP);
	else
		return (SUCCESS);
}

int	line_loop(int *i, char **line, t_big *datas)
{
	int		ret;
	int		ret2;
	int		non_print_flag;
	char	buf[7];

	while ((*line)[*i] != '\n')
	{
		ret = initiate_line_buffer(buf, &non_print_flag);
		ret2 = interpret_signal(line, i);
		if (!ret || !ret2)
			return (ERROR);
		else if (ret == BREAK_LOOP)
			break ;
		check_if_non_print(buf, &non_print_flag, datas);
		if (non_print_flag || g_tcaps.cursor_pos < *i)
			ret = launch_termcaps(buf, line, i, datas);
		else
			ret = edit_and_print_line(buf, line, i);
		if (ret == BREAK_LOOP)
			break ;
		if (!ret)
			return (ERROR);
	}
	return (SUCCESS);
}

char	*initialize_line_activate_tc(void)
{
	int		ret;
	char	*line;

	line = ft_strdup("");
	if (!(line))
		return (printc_stderr(0, strerror(errno), 0));
	ret = raw_mode();
	if (!ret)
		return (ERROR);
	ret = cursor_position();
	if (!ret)
		return (ERROR);
	return (line);
}

char	*create_line(t_big *datas)
{
	int		ret;
	char	*line;
	int		i;

	i = 0;
	line = initialize_line_activate_tc();
	if (!line)
		return (ERROR);
	line_loop(&i, &line, datas);
	ret = normal_mode();
	if (!ret)
		return (ERROR);
	ft_putchar('\n');
	return (line);
}
