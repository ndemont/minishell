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

int	scroll_n_times(int n)
{
	int		ret;
	char	*sf_cap;

	ret = 0;
	sf_cap = tgetstr("sf", NULL);
	if (!sf_cap)
		return (printi_stderr(0, strerror(errno), 0));
	while (n)
	{
		ret = tputs(sf_cap, 1, ft_putchar2);
		if (ret == ERR)
			return (printi_stderr(0, "tputs error in scroll_n_times\n", 0));
		n--;
	}
	return (SUCCESS);
}

int	clear_term(void)
{
	int	ret;
	int	cursor_flag;
	int	decrement;

	ret = SUCCESS;
	cursor_flag = 0;
	if (g_tcaps.l_max - 1 <= g_tcaps.cursor_lvl)
		return (SUCCESS);
	decrement = g_tcaps.l_max - 1 - g_tcaps.cursor_lvl;
	if (decrement)
	{
		cursor_flag = 1;
		ret = scroll_n_times(decrement);
		if (!ret)
			return (ERROR);
	}
	if (cursor_flag)
		ret = move_cursor(g_tcaps.c_pos, g_tcaps.cursor_lvl);
	return (ret);
}
