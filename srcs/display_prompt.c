/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:02:15 by ndemont           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/03/26 17:34:58 by ndemont          ###   ########.fr       */
=======
/*   Updated: 2021/03/26 15:21:51 by ndemont          ###   ########.fr       */
>>>>>>> lexer debut
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_prompt(void)
{
	write(1, PURPLE, 7);
	write(1, "minishellrose-v1$ ", 18);
   	write(1, RESET, 6);
	return (1);
}

int	read_input(void)
{
	int ret;
	char *line;

	display_prompt();
	ret = get_next_line(0, &line);
	ft_lexer(line);
	return (ret);
}
