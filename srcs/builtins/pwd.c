/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:58:06 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/16 17:41:35 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_big *datas)
{
	char *pwd;
	t_list *tmp;

	(void)datas;
	tmp = *datas->env;
	pwd = getcwd(NULL, 0); //Should I control errno ??
	if (!pwd)
	{
		while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "PWD"))
			tmp = tmp->next;
		if (tmp && !ft_strcmp(((t_var *)tmp->content)->var, "PWD"))
			pwd=ft_strdup(((t_var *)tmp->content)->value);
		ft_putstr(pwd);
		ft_putchar('\n');
		return (-1);
	}
	ft_putstr(pwd);
	ft_putchar('\n');
	free(pwd);
	return (0);
}
