/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:00:28 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/19 12:30:55 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_single_quote(char *input, int *i, int *j)
{
	char	*arg;

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

char	*get_first_quote(char *new, char *input, int *i, int start)
{
	char	*first;
	char	*tmp;

	tmp = new;
	first = ft_substr(input, start, *i - start);
	if (!(first))
	{
		free(tmp);
		return (printc_stderr(0, strerror(errno), 0));
	}
	new = ft_strjoin(new, first);
	if (!(new))
	{
		clean_free(&tmp);
		clean_free(&first);
		return (printc_stderr(0, strerror(errno), 0));
	}
	clean_free(&tmp);
	clean_free(&first);
	return (new);
}

char	*get_var_quotes(char *input, int *i, char *new, int *start)
{
	char	*tmp;

	if (input[*i] == '$')
	{	
		tmp = new;
		new = get_first_quote(new, input, i, *start);
		if (!(new))
		{
			clean_free(&tmp);
			return (0);
		}
		clean_free(&tmp);
		tmp = new;
		new = get_variable_part(new, input, i);
		if (!(new))
		{
			clean_free(&tmp);
			return (0);
		}
		clean_free(&tmp);
		*start = *i;
	}
	else
		*i = *i + 1;
	return (new);
}

char	*get_double_quote(char *input, int *i, int j)
{
	char	*new;
	char	*tmp;
	int		start;

	new = ft_substr(input, j, *i - j);
	if (!(new))
		return (printc_stderr(0, strerror(errno), 0));
	*i = *i + 1;
	start = *i;
	while (input[*i] && input[*i] != '\"')
	{
		new = get_var_quotes(input, i, new, &start);
		if (!new)
			return (0);
	}
	tmp = new;
	new = get_first_quote(new, input, i, start);
	if (!(new))
		return (0);
	*i = *i + 1;
	return (new);
}
