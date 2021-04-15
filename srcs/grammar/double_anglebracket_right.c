/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_anglebracket_right.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:10:44 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/15 14:11:31 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_file(char *str, char *path)
{
	int fd;

	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	ft_putstr_fd(str, fd);
	close(fd);
}
