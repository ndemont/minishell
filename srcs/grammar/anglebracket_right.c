/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anglebracket_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:10:15 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/15 14:36:16 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	overwrite_file(char *str, char *path)
{
	int fd;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_putstr_fd(str, fd);
	close(fd);
}

void	exec_anglebracket_right(char **argv, t_big *datas)
{
	int fd;

	printf("arg[0] = %s", argv[0]);
	fd = open(argv[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	printf("datas->fd = %i", datas->fd);
	dup2(datas->fd, fd);
	close(fd);
}

void	redirections(int type, char **argv, t_big *datas)
{
	if (type == 3)
		exec_anglebracket_right(argv, datas);
	//else if (type == 3)
	//	append_file(str, path);
	//else if (type == 4)
	//	redirect_file(path);
}
