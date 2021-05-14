/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:27:45 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/14 12:46:19 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_variable(char *str, int *k)
{
	char	*new;
	char	*tmp;
	int		start;

	start = *k;
	*k = *k + 1;
	while (str[*k] && str[*k] != ' ' && str[*k] != '\"' && str[*k] != '$')
		*k = *k + 1;
	if (!(new = ft_substr(str, start, *k - start)))
		return (printc_stderr(0, strerror(errno), 0));
	tmp = new;
	if (!(new = ft_strjoin("\"", tmp)))
	{
		free(tmp);
		return (printc_stderr(0, strerror(errno), 0));
	}
	tmp = new;
	if (!(new = ft_strjoin(tmp, "\"")))
	{
		free(tmp);
		return (printc_stderr(0, strerror(errno), 0));
	}
	free(tmp);
	return (new);
}

char		*get_str(char *input, int *i, int j)
{
	char	*new;
	char	*tmp;
	int		end;

	new = 0;
	if (input[j] != '$')
	{
		new = ft_substr(input, j, *i - j);
		if (!new)
			return (printc_stderr(0, strerror(errno), 0));
	}
	else if (input[j] == '$')
	{
		end = j + 1;
		while (input[end] && input[end] != ' ' && input[end] != '\'' && input[end] != '"' && input[end] != '\t' && input[end] != '\\' && input[end] != '$')
			end++;
		new = ft_substr(input, j, end - j);
		if (!new)
			return (printc_stderr(0, strerror(errno), 0));
		tmp = new;
		new = ft_strjoin("\"", tmp);
		if (!new)
		{
			free(tmp);
			return (printc_stderr(0, strerror(errno), 0));
		}
		free(tmp);
		tmp = new;
		new = ft_strjoin(new, "\"");
		if (!new)
		{
			free(tmp);
			return (printc_stderr(0, strerror(errno), 0));
		}
		free(tmp);
		*i = end;
	}
	return (new);
}

char		*get_second_part(char *input, int *i)
{
	int		j;
	char	*second_part;
	
	j = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\'' && input[*i] != '"' && input[*i] != '\t' && input[*i] != '\\')
		*i = *i + 1;
	if (input[*i] == '\\')
		second_part = get_backslash(input, i, j);
	else if (input[j] == '\'')
	{
		second_part = get_single_quote(input, i, &j);
		if (!second_part)
			return (print_errors(strerror(errno), 1));
	}
	else if (input[j] == '\"')
		second_part = get_double_quote(input, i, j);
	else
		second_part = get_str(input, i, j);
	if (!second_part)
		return (0);
	return (second_part);
}

char		*get_arg(char *input, int *i)
{
	char	*arg;
	char	*first_part;
	char	*second_part;

	arg = malloc(sizeof(char));
	if (!arg)
		return (printc_stderr(0, strerror(errno), 0));
	arg[0] = '\0';
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		*i = *i + 1;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t')
	{
		first_part = arg;
		if (!(second_part = get_second_part(input, i)))
		{
			free(first_part);
			return (0);
		}
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
