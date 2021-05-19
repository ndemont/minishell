/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:19:04 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/19 15:13:46 by ndemont          ###   ########.fr       */
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
	g_tcaps.line_lvl = 0;
	g_tcaps.child = 0;
	g_tcaps.signal = 0;
	g_tcaps.exit = 1;
	g_tcaps.cursor_max = 0;
	g_tcaps.cursor_lvl = 0;
	g_tcaps.cursor_pos = 0;
	datas->redirection_arg = 0;
	datas->file_name = 0;
	datas->browse = 0;
	datas->input = 0;
}

void	init_data(t_big *datas)
{
	datas->file_name = 0;
	datas->env = 0;
	datas->quit = 0;
	datas->export = 0;
	datas->hidden = 0;
	datas->history = 0;
	datas->quit = 0;
	datas->root = 0;
	g_tcaps.ret = 0;
	g_tcaps.c_max = 0;
	g_tcaps.l_max = 0;
	g_tcaps.c_pos = 0;
	g_tcaps.l_pos = 0;
	g_tcaps.c_start = 0;
	g_tcaps.line_lvl = 0;
	g_tcaps.signal = 0;
	g_tcaps.cursor_max = 0;
	g_tcaps.cursor_lvl = 0;
	g_tcaps.cursor_pos = 0;
	g_tcaps.current_dir = NULL;
	g_tcaps.current_dir = getcwd(g_tcaps.current_dir, 0);
}

int	main(int ac, char **av, char **env)
{
	t_big	datas;
	int		ret;

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
	ret = 1;
	while (ret)
		ret = read_input(&datas);
	if (!(update_history_file(&datas)))
		return (free_datas(&datas));
	free_datas(&datas);
	return (0);
}
