/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 12:29:43 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/14 12:48:18 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_backslash(char *input, int *i, int j)
{
	char *first_part;
	char *second_part;
	char *new;

	new = 0;
	if (input[*i] == '\\' && input[*i + 1])
	{
		*i = *i + 1;
		if (!(first_part = ft_substr(input, j, *i - j - 1)))
			return (printc_stderr(0, strerror(errno), 0));
		if (!(second_part = ft_substr(input, *i, 1)))
		{
			free(first_part);
			return (printc_stderr(0, strerror(errno), 0));
		}
		new = ft_strjoin(first_part, second_part);
		free(first_part);
		free(second_part);
		if (!new)
			return (printc_stderr(0, strerror(errno), 0));
		*i = *i + 1;
	}
	else if (input[*i] == '\\' && !input[*i + 1])
		return (printc_stderr(0, "missing char at end of line", 1));
	return (new);
}

char		*get_single_quote(char *input, int *i, int *j)
{
	char *arg;

	arg = 0;
	if (input[*i] == '\'')
	{
		*i = *i + 1;
		while (input[*i] != '\'')
			*i = *i + 1;
		arg = ft_substr(input, *j + 1, *i - *j - 1);
		if (!arg)
			return (printc_stderr(0, strerror(errno), 0));
		*i = *i + 1;
	}
	else if (input[*i] == '"')
	{
		*i = *i + 1;
		while (input[*i] != '"')
			*i = *i + 1;
		arg = ft_substr(input, *j + 1, *i - *j - 1);
		if (!arg)
			return (printc_stderr(0, strerror(errno), 0));
		*i = *i + 1;
	}
	return (arg);
}

char		*get_double_quote(char *input, int *i, int j)
{
	char	*new;
	char	*tmp;
	char	*first_part;
	char	*second_part;
	int 	start;

	if (!(new = ft_substr(input, j, *i - j)))
		return (printc_stderr(0, strerror(errno), 0));
	*i = *i + 1;
	start = *i;
	while (input[*i] && input[*i] != '\"')
	{
		if (input[*i] == '$')
		{
			tmp = new;
			if (!(first_part = ft_substr(input, start, *i - start)))
			{
				free(tmp);
				return (printc_stderr(0, strerror(errno), 0));
			}
			if (!(new = ft_strjoin(new, first_part)))
			{
				free(tmp);
				free(first_part);
				return (printc_stderr(0, strerror(errno), 0));
			}
			free(tmp);
			free(first_part);
			if (!(second_part = get_variable(input, i)))
			{
				free(first_part);
				free(new);
				return (printc_stderr(0, strerror(errno), 0));
			}
			tmp = new;
			if (!(new = ft_strjoin(new, second_part)))
			{
				free(first_part);
				free(tmp);
				return (printc_stderr(0, strerror(errno), 0));
			}
			free(tmp);
			free(second_part);
			start = *i;
		}
		else
			*i = *i + 1;
	}
	tmp = new;
	if (!(first_part = ft_substr(input, start, *i - start)))
	{
		free(new);
		return (printc_stderr(0, strerror(errno), 0));
	}
	if (!(new = ft_strjoin(new, first_part)))
	{
		free(tmp);
		free(first_part);
		return (printc_stderr(0, strerror(errno), 0));
	}
	free(tmp);
	free(first_part);
	*i = *i + 1;
	return (new);
}
