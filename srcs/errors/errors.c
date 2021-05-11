/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:27:26 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/11 22:54:27 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*print_errors(char *error, int exit)
{
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	tcaps.exit = exit;
	return (0);
}

int		print_errors_int(char *error, int exit)
{
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	tcaps.exit = exit;
	return (0);
}

char	**print_stderr(char *str1, char *str2, char *str3, int exit)
{
	if (str1)
		ft_putstr_fd(str1, STDERR_FILENO);
	else 
		ft_putstr_fd("minishellrose :", STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	if (str3)
		ft_putstr_fd(str3, STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
	tcaps.exit = exit;
	return (0);
}