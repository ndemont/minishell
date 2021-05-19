/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:10:15 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/19 11:36:18 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_std_fd(int fd_in, int fd_out)
{
	char	*line;
	int		ret;

	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd_in, &line);
		ft_putstr_fd(line, fd_out);
		ft_putstr_fd("\n", fd_out);
		free(line);
		line = 0;
	}
	ft_putstr_fd(line, fd_out);
	if (line)
		free(line);
	line = 0;
}

int	exec_anglebracket_right(char **argv, t_big *datas)
{
	int	ret;

	datas->flag_pipe = 0;
	datas->flag_left_bracket = 1;
	if (datas->fd_out != STDOUT_FILENO)
		close(datas->fd_out);
	datas->fd_out = open(argv[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (datas->fd_out < 0)
		return (printi_stderr(0, strerror(errno), 0));
	ret = ft_copy_arg(argv, datas);
	if (!ret)
		return (0);
	datas->file_name = ft_strdup(argv[0]);
	if (!datas->file_name)
		return (printi_stderr(0, strerror(errno), 0));
	datas->flag_bracket = 1;
	return (1);
}

int	exec_anglebracket_left(char **argv, t_big *datas)
{
	int	fd;

	datas->flag_pipe = 0;
	fd = open(argv[0], O_RDONLY);
	if (fd < 0)
	{
		printi_stderr(argv[0], ": No such file or directory", 1);
		if (datas->flag_left_bracket == 0)
			datas->fd = open(".hidden", O_CREAT | O_APPEND, 0644);
	}
	else
	{
		if (datas->flag_left_bracket == 0)
			datas->fd = fd;
	}
	datas->flag_bracket = 1;
	return (1);
}

int	exec_double_anglebracket_right(char **argv, t_big *datas)
{
	int	ret;

	datas->flag_pipe = 0;
	datas->flag_left_bracket = 1;
	if (datas->fd_out != STDOUT_FILENO)
		close(datas->fd_out);
	datas->fd_out = open(argv[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (datas->fd_out < 0)
		return (printi_stderr(0, strerror(errno), 0));
	ret = ft_copy_arg(argv, datas);
	if (!ret)
		return (0);
	datas->file_name = ft_strdup(argv[0]);
	if (!datas->file_name)
		return (printi_stderr(0, strerror(errno), 0));
	datas->flag_bracket = 1;
	return (1);
}

void	redirections(int type, char **argv, t_big *datas)
{
	int	ret;

	if (type == 2)
		ret = exec_double_anglebracket_right(argv, datas);
	else if (type == 3)
		ret = exec_anglebracket_right(argv, datas);
	else if (type == 4)
		ret = exec_anglebracket_left(argv, datas);
}
