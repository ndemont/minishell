/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:58:24 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/20 19:17:54 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_builtin(t_node *token)
{
	static char	*list[7] = \
	{"echo", "export", "env", "cd", "pwd", "unset", "exit"};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (!token->arg[0])
			break ;
		if (!ft_strcmp(list[i], token->arg[0]))
		{
			token->builtin = token->command;
			token->command = 0;
			break ;
		}
		i++;
	}
	if (token->command && ft_strchr(token->command, '='))
	{
		token->builtin = token->command;
		token->command = 0;
	}
}

int	get_command(t_node *token)
{
	int			i;
	int			j;
	int			count;

	i = 0;
	count = count_arg(token->input);
	if (!count)
	{
		token = 0;
		return (1);
	}
	token->arg = (char **)malloc(sizeof(char *) * (count + 1));
	if (!token->arg)
		return (print_errors_int(strerror(errno), 1));
	j = 0;
	while (token->input[i] && j < count)
	{
		token->arg[j] = get_arg(token->input, &i);
		j++;
	}
	token->arg[j] = 0;
	token->command = ft_strdup(token->arg[0]);
	search_builtin(token);
	return (1);
}

t_node	**ft_parser(t_node **token_tab)
{
	int	i;

	i = 0;
	while (token_tab[i])
	{
		if (!token_tab[i]->type)
			get_command(token_tab[i]);
		i++;
	}
	if (token_tab[i - 1]->type > 0 && token_tab[i - 1]->type < 5)
	{
		g_tcaps.ret = 2;
		return (print_errors("syntax error", 1));
	}
	return (token_tab);
}
