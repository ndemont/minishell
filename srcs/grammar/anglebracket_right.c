/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anglebracket_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:10:15 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/15 15:49:38 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_std_fd(int fd_in, int fd_out)
{
	char	*line;
	int 	ret;

	while ((ret = get_next_line(fd_in, &line)) > 0)
	{
		ft_putstr_fd(line, fd_out);
		ft_putstr_fd("\n", fd_out);
		free(line);
	}
	ft_putstr_fd(line, fd_out);
	free(line);
}

void	exec_anglebracket_right(char **argv, t_big *datas)
{
	int fd;

	datas->flag_pipe = 0;
	fd = open(argv[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	print_std_fd(datas->fd, fd);
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
