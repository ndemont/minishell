/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:27:45 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/22 00:14:11 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cat_var(char **new, char *str, int *j, int start)
{
	*new = get_first_quote(new, str, j, start);
	if (!(*new))
		return (0);
	*new = get_variable_part(new, str, j);
	if (!(*new))
		return (0);
	return (*new);
}

char	*get_str(char *str, int *i, int j)
{
	char	*new;
	int		start;

	new = malloc(sizeof(char));
	new[0] = 0;
	start = j;
	while (j < *i)
	{
		if (str[j] == '$')
		{
			new = cat_var(&new, str, &j, start);
			if (!new)
				return (0);
			start = j;
		}
		else
			j++;
	}
	if (start != j)
	{
		new = get_first_quote(&new, str, &j, start);
		if (!new)
			return (0);
	}
	return (new);
}

char	*get_second_part(char *input, int *i, char *arg)
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

char	*init_arg(void)
{
	char	*arg;

	arg = malloc(sizeof(char));
	if (!(arg))
		return (printc_stderr(0, strerror(errno), 0));
	arg[0] = '\0';
	return (arg);
}

char	*get_arg(char *input, int *i)
{
	char	*arg;
	char	*first_part;
	char	*second_part;

	arg = init_arg();
	if (!(arg))
		return (printc_stderr(0, strerror(errno), 0));
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		*i = *i + 1;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t')
	{
		first_part = arg;
		second_part = get_second_part(input, i, arg);
		if (!(second_part))
			return (0);
		arg = ft_strjoin(first_part, second_part);
		if (!(arg))
		{
			free(first_part);
			free(second_part);
		}
		free(first_part);
		free(second_part);
	}
	return (arg);
}
