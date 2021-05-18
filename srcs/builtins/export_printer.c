/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 11:15:54 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/18 11:15:55 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_list **list)
{
	t_list *tmp;

	tmp = *list;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(((t_var *)tmp->content)->var, STDOUT_FILENO);
		if (((t_var *)tmp->content)->value)
		{
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
			ft_putstr_fd(((t_var *)tmp->content)->value, STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		tmp = tmp->next;
	}
}
