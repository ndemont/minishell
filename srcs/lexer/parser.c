/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:58:24 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/14 15:23:43 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_builtin(t_node *token)
{
	static char	*list[7] = {"echo", "export", "env", "cd", "pwd", "unset", "exit"};
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
	return (1);
}

t_node		**ft_builtin_parser(t_node **token_tab)
{
	int i;

	i = 0;
	while (token_tab[i])
	{
		if (!token_tab[i]->type)
			get_builtin(token_tab[i]);
		i++;
	}
	if (token_tab[i - 1]->type > 0 && token_tab[i - 1]->type < 5)
		return (print_errors("Missing command at end of line", 0));
	return (token_tab);
}
