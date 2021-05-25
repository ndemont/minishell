/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:15:04 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/25 15:09:45 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_return_value(void)
{
	char	*value;

	value = ft_itoa(g_tcaps.ret);
	return (value);
}

static char	*cat_value(char *new, int *i, int *start)
{
	char	*value;
	char	*tmp;

	value = get_return_value();
	if (!value)
	{
		free(new);
		return (printc_stderr(0, strerror(errno), 0));
	}
	tmp = new;
	new = ft_strjoin(new, value);
	free(tmp);
	free(value);
	if (!new)
		return (printc_stderr(0, strerror(errno), 0));
	(*i) += 4;
	(*start) = *i;
	return (new);
}

static char	*cat_str(char *str, char *new, int *i, int start)
{
	while (str[*i] && (str[*i] != '"' || str[*i + 1] != '$'))
		(*i)++;
	new = get_first_quote(new, str, i, start);
	if (!new)
		return (0);
	return (new);
}

char	*check_arg_var(char *str)
{
	int		i;
	int		start;
	char	*new;

	i = 0;
	start = 0;
	new = ft_strdup("");
	if (!new)
		return (printc_stderr(0, strerror(errno), 0));
	while (str[i])
	{
		if (str[i] == '"' && str[i + 1] == '$' && str[i + 2] == '?')
			new = cat_value(new, &i, &start);
		else
			new = cat_str(str, new, &i, start);
		if (!new)
		{
			clean_free(&str);
			return (0);
		}
	}
	clean_free(&str);
	return (new);
}
