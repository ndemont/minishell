/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:58:06 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/12 13:58:08 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_big *datas)
{
	char *pwd;

	(void)datas;
	pwd = getcwd(NULL, 0); //Should I control errno ??
	if (!pwd)
		return (-1);
	ft_putstr(pwd);
	ft_putchar('\n');
	free(pwd);
	return (0);
}
