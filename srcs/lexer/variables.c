/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 17:48:20 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/19 12:17:00 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable_str(char *input, int *i, int end, int j)
{
	char	*new;
	char	*tmp;

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
	return (new);
}

char	*get_variable_quotes(char *str, int *k)
{
	char	*new;
	char	*tmp;
	int		start;

	start = *k;
	*k = *k + 1;
	while (ft_isalnum(str[*k]) || str[*k] == '_' || str[*k] == '?')
		*k = *k + 1;
	new = ft_substr(str, start, *k - start);
	if (!(new))
		return (printc_stderr(0, strerror(errno), 0));
	tmp = new;
	new = ft_strjoin("\"", tmp);
	clean_free(&tmp);
	if (!(new))
		return (printc_stderr(0, strerror(errno), 0));
	tmp = new;
	new = ft_strjoin(tmp, "\"");
	clean_free(&tmp);
	if (!(new))
		return (printc_stderr(0, strerror(errno), 0));
	return (new);
}

char	*get_variable_part(char *new, char *input, int *i)
{
	char	*variable;
	char	*tmp;

	variable = get_variable_quotes(input, i);
	if (!(variable))
	{
		free(new);
		return (0);
	}
	tmp = new;
	new = ft_strjoin(new, variable);
	if (!(new))
	{
		free(tmp);
		return (printc_stderr(0, strerror(errno), 0));
	}
	free(tmp);
	free(variable);
	return (new);
}
