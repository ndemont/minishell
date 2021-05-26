/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:02:15 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/20 19:19:10 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	variable_init(char **line, t_node ***token_tab, t_big *datas)
{
	actualize_data(datas);
	*line = NULL;
	datas->quit = 0;
	display_prompt();
	*token_tab = 0;
}

static int	clean_line(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = 0;
	}
	return (1);
}

int	read_input(t_big *datas)
{
	char	*line;
	t_node	**token_tab;

	variable_init(&line, &token_tab, datas);
	line = create_line(datas);
	if (!line)
		return (g_tcaps.exit);
	else if (!line[0])
		return (clean_line(&line));
	save_history(line, datas);
	token_tab = ft_lexer(line);
	clean_free(&line);
	if (!token_tab)
		return (g_tcaps.exit);
	if (!ft_parser(token_tab))
	{
		free_tokens(token_tab);
		return (g_tcaps.exit);
	}
	tree(token_tab, datas);
	executions(datas);
	if (!g_tcaps.exit)
		return (0);
	return (1);
}
