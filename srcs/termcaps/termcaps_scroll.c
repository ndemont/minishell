/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_scroll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 10:18:12 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/03 10:18:15 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	scroll_n_times(int n)
{
	char *sf_cap;

	sf_cap = tgetstr("sf", NULL);
	if (!sf_cap)
		exit(0);
	while (n)
	{
		tputs(sf_cap, 1, ft_putchar2);
		n--;
	}
}

void	clear_term(void)
{
	int		cursor_flag;
	int		decrement;

	cursor_flag = 0;
	if (tcaps.l_max - 1 <= tcaps.cursor_lvl)
		return ;
	decrement = tcaps.l_max - 1 - tcaps.cursor_lvl;
	if (decrement)
	{
		cursor_flag = 1;
		scroll_n_times(decrement);
	}
	if (cursor_flag)
		move_cursor(tcaps.c_pos, tcaps.cursor_lvl);
}
