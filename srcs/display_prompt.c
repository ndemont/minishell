/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:02:15 by ndemont           #+#    #+#             */
/*   Updated: 2021/03/22 16:19:34 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_prompt(void)
{
	write(1, PURPLE, 10);
	write(1, "minishellrose-v1$ ", 18);
   	write(1, RESET, 9);
	return (1);
}

int	read_input(void)
{
	int ret;
	char *line;

	display_prompt();
	ret = get_next_line(0, line);
	return (ret);
}
