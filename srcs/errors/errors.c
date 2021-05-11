/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:27:26 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/11 11:57:39 by ndemont          ###   ########.fr       */
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