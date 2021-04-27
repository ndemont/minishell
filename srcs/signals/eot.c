/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 13:46:13 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/27 14:29:10 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    end_of_transmission(t_big *datas)
{
 	(void)datas;
     //free_tokens(token_tab);
	//free_datas(datas);
    write(0, "exit\n", 5);
    exit(1);
}