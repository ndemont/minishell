/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:00:28 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/25 17:12:14 by ndemont          ###   ########.fr       */
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

	first = ft_substr(input, start, *i - start);
	if (!(first))
	{
		clean_free(&new);
		return (printc_stderr(0, strerror(errno), 0));
	}
	tmp = new;
	new = ft_strjoin(new, first);
	clean_free(&tmp);
	clean_free(&first);
	if (!(new))
		return (printc_stderr(0, strerror(errno), 0));
	return (new);
}

char	*cat_back_quotes(char *new, char *input, int *i, int *start)
{
	char	*back;
	char	*tmp;

	tmp = new;
	new = get_backslash_quotes(input, i, start);
	if (!new)
		return (0);
	back = new;
	new = ft_strjoin(tmp, back);
	clean_free(&tmp);
	clean_free(&back);
	*start = *i;
	return (new);
}

char	*get_var_quotes(char *input, int *i, char *new, int *start)
{
	if (input[*i] == '$')
	{	
		new = get_first_quote(new, input, i, *start);
		if (!(new))
			return (0);
		new = get_variable_part(new, input, i);
		*start = *i;
	}
	else if (input[*i] == '\\' && (input[*i + 1] == '"' || \
	input[*i + 1] == '\\' || input[*i + 1] == '`'))
		new = cat_back_quotes(new, input, i, start);
	else
		*i = *i + 1;
	if (!(new))
		return (0);
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
