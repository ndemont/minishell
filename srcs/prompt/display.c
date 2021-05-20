/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 09:34:26 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/20 09:37:28 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_directory(void)
{
	char	*tmp;

	write(STDOUT_FILENO, CYAN, 7);
	write(STDOUT_FILENO, "(", 1);
	if (!ft_strcmp(g_tcaps.current_dir, "/"))
		write(STDOUT_FILENO, "\\", 1);
	else
	{
		tmp = ft_strrchr(g_tcaps.current_dir, '/');
		write(STDOUT_FILENO, tmp + 1, ft_strlen(tmp) - 1);
	}
	write(STDOUT_FILENO, ") ", 2);
	write(STDOUT_FILENO, RESET, 6);
	return (1);
}

int	display_prompt(void)
{
	write(STDOUT_FILENO, PURPLE, 7);
	write(STDOUT_FILENO, "minishellrose$ ", 15);
	display_directory();
	write(STDOUT_FILENO, RESET, 6);
	raw_mode();
	cursor_position();
	g_tcaps.line_lvl = 0;
	g_tcaps.cursor_lvl = 0;
	g_tcaps.c_start = g_tcaps.c_pos;
	g_tcaps.cursor_max = g_tcaps.c_start;
	g_tcaps.cursor_pos = 0;
	normal_mode();
	return (1);
}
