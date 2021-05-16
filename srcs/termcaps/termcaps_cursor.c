/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_cursor_mvmt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 10:17:00 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/03 10:17:01 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	move_cursor(int c, int l)
{
	int		ret;
	char	*cm_cap;

	cm_cap = tgetstr("cm", NULL);
	if (!cm_cap)
		return (printi_stderr(0, strerror(errno), 0));
	ret = tputs(tgoto(cm_cap, c, l), 1, ft_putchar2);
	if (ret == ERR)
		return (printi_stderr(0, "tputs failed in move_cursor", 0));
	actualize_cursor(c, l);
	return (1);
}

int	cursor_position(void)
{
	int		ret;
	char	buf[100];
	int		i;

	ret = term_size();
	if (!ret)
		return (ret);
	ft_bzero(buf, 100);
	write(STDOUT_FILENO, "\033[6n", 4);
	read(STDOUT_FILENO, buf, 100);
	i = 0;
	while (buf[i] && i < 100 && !ft_isdigit(buf[i]))
		i++;
	tcaps.l_pos = ft_atoi(buf + i) - 1;
	while (buf[i] && i < 100 && ft_isdigit(buf[i]))
		i++;
	while (buf[i] && i < 100 && !ft_isdigit(buf[i]))
		i++;
	tcaps.c_pos = ft_atoi(buf + i) - 1;
	if (tcaps.l_pos < 0 || tcaps.c_pos < 0)
	{
		tcaps.l_pos = 0;
		tcaps.c_pos = 0;
	}
	return (1);
}

int	move_cursor_left(void)
{
	int	ret;

	ret = SUCCESS;
	if ((tcaps.c_pos - 1 >= tcaps.c_start && !tcaps.cursor_lvl) || \
	(tcaps.c_pos - 1 >= 0 && tcaps.cursor_lvl))
	{
		ret = move_cursor(tcaps.c_pos - 1, tcaps.l_pos);
		tcaps.cursor_pos--;
	}
	else if (tcaps.c_pos - 1 < 0 && tcaps.cursor_lvl)
	{
		ret = move_cursor(tcaps.c_max - 1, tcaps.l_pos - 1);
		tcaps.cursor_lvl--;
		tcaps.cursor_pos--;
	}
	return (ret);
}

int	move_cursor_right(void)
{
	int	ret;

	ret = SUCCESS;
	if (tcaps.cursor_lvl == tcaps.line_lvl)
	{
		if (tcaps.c_pos + 1 <= tcaps.cursor_max)
		{
			ret = move_cursor(tcaps.c_pos + 1, tcaps.l_pos);
			tcaps.cursor_pos++;
		}
	}
	else if (tcaps.cursor_lvl < tcaps.line_lvl)
	{
		if (tcaps.c_pos + 1 < tcaps.c_max)
			ret = move_cursor(tcaps.c_pos + 1, tcaps.l_pos);
		else
		{
			ret = move_cursor(0, tcaps.l_pos + 1);
			tcaps.cursor_lvl++;
		}
		tcaps.cursor_pos++;
	}
	return (ret);
}

int	clear_after_cursor(void)
{
	int		ret;
	char	*cd_cap;

	cd_cap = tgetstr("cd", NULL);
	if (!cd_cap)
		return (printi_stderr(0, strerror(errno), 0));
	ret = tputs(cd_cap, 1, ft_putchar2);
	if (ret == ERR)
		return (printi_stderr(0, "tputs failed in move_cursor", 0));
	return (1);
}
