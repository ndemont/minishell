/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_backspace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 10:22:24 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/03 10:22:34 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*backspace_line_edition(int *i, char **line)
{
	char	*oldline;

	oldline = *line;
	if (*i > 0)
		(*i)--;
	*line = ft_substr(oldline, 0, *i);
	if (oldline)
		free(oldline);
	return (*line);
}

void	initiate_deletion_caps(char **dc_cap, char **ce_cap, int *ret)
{
	*dc_cap = tgetstr("dc", NULL);
	*ce_cap = tgetstr("ce", NULL);
	*ret = SUCCESS;
}

int	backspace_first_case(char *dc_cap)
{
	int	ret;

	ret = move_cursor(tcaps.c_pos - 1, tcaps.l_pos);
	if (!ret)
		return (ERROR);
	ret = tputs(dc_cap, 1, ft_putchar2);
	if (ret == ERR)
		return (printi_stderr(0, "tputs failed in backspace_first_case\n", 0));
	tcaps.cursor_max--;
	return (SUCCESS);
}

int	backspace_second_case(char *ce_cap)
{
	int	ret;

	ret = move_cursor(tcaps.c_max - 1, tcaps.l_pos - 1);
	if (!ret)
		return (ERROR);
	ret = tputs(ce_cap, 1, ft_putchar2);
	if (ret == ERR)
		return (printi_stderr(0, "tputs failed in backspace_first_case\n", 0));
	tcaps.line_lvl--;
	tcaps.cursor_lvl--;
	tcaps.cursor_max = tcaps.c_max - 1;
	return (SUCCESS);
}

int	backspace(int *i, char **line)
{
	int		ret;
	char	*dc_cap;
	char	*ce_cap;

	*line = backspace_line_edition(i, line);
	initiate_deletion_caps(&dc_cap, &ce_cap, &ret);
	if (!(*line) || !dc_cap || !ce_cap)
		return (printi_stderr(0, strerror(errno), 0));
	if ((tcaps.c_pos - 1 >= tcaps.c_start && !tcaps.line_lvl) || \
	(tcaps.c_pos - 1 >= 0 && tcaps.line_lvl))
		ret = backspace_first_case(dc_cap);
	else if (tcaps.c_pos - 1 < 0 && tcaps.line_lvl)
		ret = backspace_second_case(ce_cap);
	tcaps.cursor_pos = *i;
	if (!ret)
		return (ERROR);
	return (SUCCESS);
}
