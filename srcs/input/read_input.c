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
