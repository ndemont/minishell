/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:27:26 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/21 11:43:51 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*print_errors(char *error, int exit)
{
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	g_tcaps.exit = exit;
	return (0);
}

int	print_errors_int(char *error, int exit)
{
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	g_tcaps.exit = exit;
	return (0);
}

char	**printcc_stderr(char *cmd, char *sterror, int exit)
{
	ft_putstr_fd("minishellrose: ", STDERR_FILENO);
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(sterror, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_tcaps.exit = exit;
	return (0);
}

char	*printc_stderr(char *cmd, char *sterror, int exit)
{
	ft_putstr_fd("minishellrose: ", STDERR_FILENO);
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(sterror, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_tcaps.exit = exit;
	return (0);
}

int	printi_stderr(char *cmd, char *sterror, int exit)
{
	ft_putstr_fd("minishellrose: ", STDERR_FILENO);
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(sterror, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_tcaps.exit = exit;
	return (0);
}
