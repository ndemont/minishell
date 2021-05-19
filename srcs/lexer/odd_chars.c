/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd_chars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 12:29:43 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/19 12:17:19 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_tilde(int *i)
{
	char	*tilde;

	tilde = ft_strdup("\"$HOME\"");
	if (!tilde)
		printc_stderr(0, strerror(errno), 0);
	*i = *i + 1;
	return (tilde);
}

char	*remove_backslash(char *input, int *i, int j)
{
	char	*first_part;
	char	*second_part;
	char	*new;

	*i = *i + 1;
	first_part = ft_substr(input, j, *i - j - 1);
	if (!(first_part))
		return (printc_stderr(0, strerror(errno), 0));
	second_part = ft_substr(input, *i, 1);
	if (!(second_part))
	{
		clean_free(&first_part);
		return (printc_stderr(0, strerror(errno), 0));
	}
	new = ft_strjoin(first_part, second_part);
	clean_free(&first_part);
	clean_free(&second_part);
	if (!new)
		return (printc_stderr(0, strerror(errno), 0));
	*i = *i + 1;
	return (new);
}

char	*get_backslash(char *input, int *i, int j)
{
	char	*new;

	new = 0;
	if (input[*i] == '\\' && input[*i + 1])
	{
		new = remove_backslash(input, i, j);
		if (!new)
			return (0);
	}
	else if (input[*i] == '\\' && !input[*i + 1])
		return (printc_stderr(0, "missing char at end of line", 1));
	return (new);
}
