/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:10:15 by ndemont           #+#    #+#             */
<<<<<<< HEAD:srcs/grammar/redirection.c
/*   Updated: 2021/04/21 15:25:25 by ndemont          ###   ########.fr       */
=======
/*   Updated: 2021/04/21 12:18:11 by ndemont          ###   ########.fr       */
>>>>>>> ca7fabab4c2684cde82644e8896a8f81c71ee995:srcs/grammar/redirection.c
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
		line = 0;
	}
	ft_putstr_fd(line, fd_out);
	free(line);
	line = 0;
}

void	exec_anglebracket_right(char **argv, t_big *datas)
{
	int fd;

	datas->flag_pipe = 0;
	if (datas->flag_bracket == 0)
	{
		fd = open(argv[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		print_std_fd(datas->fd, fd);
	}
	else
		fd = open(argv[0], O_CREAT | O_WRONLY, 0644);
	close(fd);
}

void	exec_anglebracket_left(char **argv, t_big *datas)
{
<<<<<<< HEAD:srcs/grammar/redirection.c
	int	fd;

	datas->flag_pipe = 0;
	fd = open(argv[0], O_RDONLY);
	if (fd < 0)
	{
		print_errors("minishellrose: No such file or directory");
		datas->quit = 1;
	}
	if (datas->flag_left_bracket == 0)
	{
		datas->fd = fd;
		datas->flag_left_bracket = 1;
	}
=======
	int fd;

	datas->flag_pipe = 0;
	fd = open(argv[0], O_RDONLY);
	datas->fd = fd;
>>>>>>> ca7fabab4c2684cde82644e8896a8f81c71ee995:srcs/grammar/redirection.c
}

void	exec_double_anglebracket_right(char **argv, t_big *datas)
{
	int fd;

	datas->flag_pipe = 0;
	fd = open(argv[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (datas->flag_bracket == 0)
		print_std_fd(datas->fd, fd);
	close(fd);
}

void	redirections(int type, char **argv, t_big *datas)
{
	if (type == 2)
		exec_double_anglebracket_right(argv, datas);
	else if (type == 3)
		exec_anglebracket_right(argv, datas);
	else if (type == 4)
		exec_anglebracket_left(argv, datas);
	datas->flag_bracket = 1;
}
