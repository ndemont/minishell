/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:02:15 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/20 09:34:57 by ndemont          ###   ########.fr       */
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

void	check_if_non_print(char *buf, int *non_print_flag, t_big *datas)
{
	int	j;

	j = 0;
	while (buf[j])
	{
		if ((int)buf[j] == 10)
			break ;
		else if (((int)buf[j] >= 0 && (int)buf[j] <= 31) || (int)buf[j] == 127)
			*non_print_flag = 1;
		j++;
	}
	if (buf[0] != 27 || buf[1] != 91 || (buf[2] != 65 && buf[2] != 66))
		datas->flag_history = 0;
}

int	launch_termcaps(char *buf, char **line, int *i, t_big *datas)
{
	int	ret;

	if (buf[0] == 10)
	{
		ret = execute_line(i, line, buf);
		if (!ret)
			return (ERROR);
		else
			return (BREAK_LOOP);
	}
	ret = do_the_right_thing(i, buf, line, datas);
	return (ret);
}

int	edit_and_print_line(char *buf, char **line, int *i)
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

int	read_input(t_big *datas)
{
	char	*line;
	t_node	**token_tab;

	actualize_data(datas);
	line = NULL;
	datas->quit = 0;
	display_prompt();
	token_tab = 0;
	line = create_line(datas);
	if (!line)
		return (g_tcaps.exit);
	else if (!line[0])
		return (1);
	save_history(line, datas);
	token_tab = ft_lexer(line);
	if (!token_tab)
		return (g_tcaps.exit);
	if (!ft_parser(token_tab))
	{
		free_tokens(token_tab);
		return (0);
	}
	tree(token_tab, datas);
	executions(datas);
	if (!g_tcaps.exit)
		return (0);
	clean_datas(datas);
	return (1);
}
