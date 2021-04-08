/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:02:15 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/08 14:58:12 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_prompt(void)
{
	write(1, PURPLE, 7);
	write(1, "minishellrose-v1$ ", 18);
   	write(1, RESET, 6);
	return (1);
}

int	read_input(t_big *datas)
{
	int		ret;
	char	*line;
	t_node	**token_tab;

	(void)datas;
	display_prompt();
	ret = get_next_line(0, &line);
	if (!ret || !line)
		return (ret);
	token_tab = ft_lexer(line);
	if (!(token_tab ))
		return (ret);
	if (!ft_builtin_parser(token_tab))
		return (ret);
	tree(token_tab, datas);
	executions(token_tab, datas);
	free_tokens(token_tab);
	return (ret);
}
