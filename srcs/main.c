/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:19:04 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/23 11:30:09 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	actualize_data(t_big *datas)
{
	datas->fd = -1;
	datas->flag_pipe = 0;
	datas->flag_bracket = 0;
	datas->flag_left_bracket = 0;
	datas->quit = 0;
	datas->root = 0;
}

void	init_data(t_big *datas)
{
	datas->fd = -1;
	datas->flag_pipe = 0;
	datas->flag_bracket = 0;
	datas->flag_left_bracket = 0;
	datas->redirection_arg = 0;
	datas->env = 0;
	datas->export = 0;
	datas->hidden = 0;
	datas->history = 0;
	datas->quit = 0;
	datas->root = 0;
	tcaps.c_max = 0;
	tcaps.l_max = 0;
	tcaps.c_pos = 0;
	tcaps.l_pos = 0;
	tcaps.c_start = 18;
}

void	sigint_handler(int sig)
{
	(void)sig;
}

int		main(int ac, char **av, char **env)
{
	t_big	datas;

	(void)ac;
	(void)av;
	termcaps_init();
	init_data(&datas);
	init_history(&datas);
	store_env(env, &datas);
	signal(SIGINT, &sigint_handler);
	while (read_input(&datas));
	update_history_file(&datas);
	return (0);
}