/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:27:45 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/14 18:09:24 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_str(char *str, int *i, int j)
{
	char	*new;
	int		end;

	new = 0;
	if (str[j] != '$')
	{
		new = ft_substr(str, j, *i - j);
		if (!new)
			return (printc_stderr(0, strerror(errno), 0));
	}
	else if (str[j] == '$')
	{
		end = j + 1;
		while (ft_isalnum(str[end]) || str[end] == '_')
			end++;
		new = get_variable_str(str, i, end, j);
		*i = end;
	}
	return (new);
}

char		*get_second_part(char *input, int *i, char *arg)
{
	int		j;
	char	*second_part;

	j = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '~'\
		&& input[*i] != '"' && input[*i] != '\'' && input[*i] != '"'\
		&& input[*i] != '\t' && input[*i] != '\\')
		*i = *i + 1;
	if (input[*i] == '\\')
		second_part = get_backslash(input, i, j);
	else if (input[j] == '\'')
		second_part = get_single_quote(input, i, &j);
	else if (input[j] == '\"')
		second_part = get_double_quote(input, i, j);
	else if (input[j] == '~')
		second_part = get_tilde(i);
	else
		second_part = get_str(input, i, j);
	if (!second_part)
	{
		free(arg);
		return (0);
	}
	return (second_part);
}

char		*get_arg(char *input, int *i)
{
	char	*arg;
	char	*first_part;
	char	*second_part;

	if (!(arg = malloc(sizeof(char))))
		return (printc_stderr(0, strerror(errno), 0));
	arg[0] = '\0';
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		*i = *i + 1;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t')
	{
		first_part = arg;
		if (!(second_part = get_second_part(input, i, arg)))
			return (0);
		if (!(arg = ft_strjoin(first_part, second_part)))
		{
			free(first_part);
			free(second_part);
		}
		free(first_part);
		free(second_part);
	}
	return (arg);
}
