/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:19:04 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/11 16:26:31 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	actualize_data(t_big *datas)
{
	datas->fd = -1;
	datas->fd_out = STDOUT_FILENO;
	datas->flag_pipe = 0;
	datas->flag_bracket = 0;
	datas->flag_left_bracket = 0;
	datas->flag_history = 0;
	datas->quit = 0;
	datas->root = 0;
	tcaps.line_lvl = 0;
	tcaps.child = 0;
	tcaps.signal = 0;
	tcaps.exit = 0;
	tcaps.cursor_max = 0;
	tcaps.cursor_lvl = 0;
	tcaps.cursor_pos = 0;
	datas->redirection_arg = 0;
	datas->file_name = 0;
	datas->browse = 0;
	datas->input = 0;
}

void	init_data(t_big *datas)
{
	datas->fd = -1;
	datas->fd_out = STDOUT_FILENO;
	datas->flag_pipe = 0;
	datas->flag_bracket = 0;
	datas->flag_left_bracket = 0;
	datas->flag_history = 0;
	datas->redirection_arg = 0;
	datas->file_name = 0;
	datas->env = 0;
	datas->quit = 0;
	datas->export = 0;
	datas->hidden = 0;
	datas->history = 0;
	datas->quit = 0;
	datas->root = 0;
	tcaps.ret = 0;
	tcaps.c_max = 0;
	tcaps.l_max = 0;
	tcaps.c_pos = 0;
	tcaps.l_pos = 0;
	tcaps.c_start = 0;
	tcaps.line_lvl = 0;
	tcaps.signal = 0;
	tcaps.cursor_max = 0;
	tcaps.cursor_lvl = 0;
	tcaps.cursor_pos = 0;
}

int		main(int ac, char **av, char **env)
{
	t_big	datas;

	(void)ac;
	(void)av;
	if (!(termcaps_init()))
		return (1);
	init_data(&datas);
	if (!(init_history(&datas)))
		return (free_datas(&datas));
	if (!(store_env(env, &datas)))
		return (free_datas(&datas)); 
	signal(SIGINT, ft_signals);
	signal(SIGQUIT, ft_signals);
	while (read_input(&datas));
	if (!(update_history_file(&datas)))
		return (free_datas(&datas));
	free_datas(&datas);
	return (0);
}
