/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 13:46:13 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/28 23:38:49 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_d(t_big *datas, char *line)
{
	if (line && !line[0])
	{
		write(0, "exit\n", 5);
		update_history_file(datas);
		//free_tokens(token_tab);
		free_datas(datas);
		exit(1);
	}
}