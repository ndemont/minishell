/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:27:45 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/30 12:56:19 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (0);
		*i = *i + 1;
	}
	else if (input[*i] == '"')
	{
		*i = *i + 1;
		while (input[*i] != '"')
			*i = *i + 1;
		arg = ft_substr(input, *j + 1, *i - *j - 1);
		if (!arg)
			return (0);
		*i = *i + 1;
	}
	return (arg);
}

char		*get_variable(char *input, int *k)
{
	char	*new;
	char	*tmp;
	int		start;

	start = *k;
	while (input[*k] && input[*k] != ' ')
		*k = *k + 1;
	new = substr(input, start, *k - start);
	if (!new)
		return (0);
	tmp = new;
	new = substr("\"", tmp, ft_strlen(tmp) + 1);
	if (!new)
	{
		free(tmp);
		return (0);
	}
	tmp = new;
	new = substr(new, "\"", tmp, ft_strlen(tmp) + 1);
	free(tmp);
	return (new);
}

char		*get_backslash(char *input, int *i, int j)
{
	char *first_part;
	char *second_part;
	char *new;

	new = 0;
	if (input[*i] == '\\' && input[*i + 1])
	{
		*i = *i + 1;
		first_part = ft_substr(input, j, *i - j - 1);
		second_part = ft_substr(input, *i, 1);
		if (!first_part || !second_part)
			return (print_errors(strerror(errno)));
		new = ft_strjoin(first_part, second_part);
		if (!new)
			return (print_errors(strerror(errno)));
		free(first_part);
		free(second_part);
		*i = *i + 1;
	}
	else if (input[*i] == '\\' && !input[*i + 1])
		print_errors("minishellrose: missing char at end of line");
	return (new);
}

char		*get_double_quote(char *input, int *i, int j)
{
	char	*tmp;
	char	*new;
	char	*var;
	int		k;
	int 	start;

	new = get_single_quote(input, i, &j);
	if (!new)
		return (print_errors(strerror(errno)));
	k = 0;
	while (new[k])
	{
		if (new[k] == '$')
		{
			if (!(var = get_variable(input, &k)))
				return (0);
			
		}
		k++;
	}
	return (new);
}

char		*get_str(char *input, int *i, int j)
{
	char *new;
	char *tmp;

	new = ft_substr(input, j, *i - j);
	if (!new)
		return (print_errors(strerror(errno)));
	if (new[0] == '$')
	{
		tmp = new;
		new = ft_strjoin("\"", tmp);
		if (!new)
			return (print_errors(strerror(errno)));
		free(tmp);
		tmp = new;
		new = ft_strjoin(new, "\"");
		if (!new)
			return (print_errors(strerror(errno)));
		free(tmp);
	}
	return (new);
}

char		*get_arg(char *input, int *i)
{
	char	*arg;
	char	*first_part;
	char	*second_part;
	int		j;

	arg = malloc(sizeof(char));
	if (!arg)
		return (print_errors(strerror(errno)));
	arg[0] = '\0';
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		*i = *i + 1;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t')
	{
		j = *i;
		first_part = arg;
		while (input[*i] && input[*i] != ' ' && input[*i] != '\'' && input[*i] != '"' && input[*i] != '\t' && input[*i] != '\\')
			*i = *i + 1;
		if (input[*i] == '\\')
			second_part = get_backslash(input, i, j);
		else if (input[j] == '\'')
		{
			second_part = get_single_quote(input, i, &j);
			if (!second_part)
				print_errors(strerror(errno));
		}
		else if (input[j] == '\"')
			second_part = get_double_quote(input, i, j);
		else
			second_part = get_str(input, i, j);
		if (!second_part)
			return (0);
		arg = ft_strjoin(first_part, second_part);
		free(first_part);
		free(second_part);
	}
	return (arg);
}
