/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:27:45 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/30 12:11:05 by ndemont          ###   ########.fr       */
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

char		*get_variable(char *input, int *i, int j)
{
	char *tmp;
	char *new;
	
	new = get_quote(input, i, &j);
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
			second_part = get_quote(input, i, &j);
			if (!second_part)
				print_errors(strerror(errno));
		}
		else if (input[j] == '\"')
			second_part = get_variable(input, i, j);
		else
			second_part = get_str(input, i , j);
		if (!second_part)
			return (0);
		arg = ft_strjoin(first_part, second_part);
		free(first_part);
		free(second_part);
	}
	return (arg);
}

int			count_arg(char *input)
{
	int count;
	int	newword;
	int i;

	count = 0;
	i = 0;
	if (!input[0])
		return (0);
	while (input[i])
	{
		newword = 0;
		if (!i)
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
				i++;
		else
		{
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			{
				if (!newword)
					newword = 1;
				i++;
			}
			if (input[i])
				count += newword;
		}
		if (!input[i])
			break ;
		while (input[i] && input[i] != ' ' && input[i] != '\'' && input[i] != '"' && input[i] != '\t' && input[i] != '\\')
			i++;
		if (input[i] == '\\' && input[i + 1])
			i += 2;
		else if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'')
				i++;
			i++;
		}
		else if (input[i] == '"')
		{
			i++;
			while (input[i] != '"')
				i++;
			i++;
		}
		else if (!input[i])
			break ;
	}
	count++;
	return (count);
}
