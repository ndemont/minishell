/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:58:06 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/06 11:25:20 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pwd_and_return(char *pwd)
{
	ft_putstr(pwd);
	ft_putchar('\n');
}

int	ft_pwd(t_big *datas)
{
	char	*pwd;
	t_list	*tmp;

	(void)datas;
	tmp = *datas->env;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		while (tmp && ft_strcmp(((t_var *)tmp->content)->var, "PWD"))
			tmp = tmp->next;
		if (((t_var *)tmp->content)->var && \
			!ft_strcmp(((t_var *)tmp->content)->var, "PWD"))
			pwd = ft_strdup(((t_var *)tmp->content)->value);
		if (!pwd)
		{
			printi_stderr(0, strerror(errno), 0);
			return (BUILT_IN_FAILURE);
		}
		print_pwd_and_return(pwd);
		return (0);
	}
	print_pwd_and_return(pwd);
	free(pwd);
	return (0);
}
