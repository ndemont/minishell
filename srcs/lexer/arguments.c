/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:27:45 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/21 21:08:30 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_str(char *str, int *i, int j)
{
	char	*new;
	char	*tmp;
	char	*tmp2;
	int		end;
	int		start;

	new = malloc(sizeof(char));
	new[0] = 0;
	start = j;
	while (j < *i)
	{
		if (str[j] == '$')
		{
			tmp2 = ft_substr(str, start, j - start);
			end = j + 1;
			while (ft_isalnum(str[end]) || str[end] == '_')
				end++;
			tmp = get_variable_str(str, &j, end, j);
			start = j;
			new = ft_strjoin(new, tmp2);
			new = ft_strjoin(new, tmp);
		}
		else
			j++;
	}
	if (start != j)
	{
		tmp = ft_substr(str, start, j - start);
		if (!tmp)
			return (printc_stderr(0, strerror(errno), 0));
		new = ft_strjoin(new, tmp);
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
