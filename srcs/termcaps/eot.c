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

void	end_of_transmission(t_big *datas, char *line)
{
	//free_tokens(token_tab);
	//free_datas(datas);
	if (line && !line[0])
	{
		write(0, "exit\n", 5);
		update_history_file(datas);
		exit(1);
	}
}