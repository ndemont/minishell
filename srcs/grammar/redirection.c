/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:10:15 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/27 21:31:20 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_std_fd(int fd_in, int fd_out)
{
	char	*line;
	int		ret;

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

void	ft_copy_arg(char **argv, t_big *datas)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (argv[i])
	{
		tmp = datas->redirection_arg;
		if (tmp)
			datas->redirection_arg = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + ft_strlen(argv[i]) + 2));
		else
			datas->redirection_arg = (char *)malloc(sizeof(char) * (ft_strlen(argv[i]) + 2));
		j = 0;
		while (argv[i][j])
		{
			datas->redirection_arg[j] = argv[i][j];
			j++;
		}
		datas->redirection_arg[j] = ' ';
		j++;
		while (tmp && *tmp)
		{
			datas->redirection_arg[j] = *tmp;
			tmp++;
			j++;
		}
		datas->redirection_arg[j] = 0;
		i++;
	}
}

void	exec_anglebracket_right(char **argv, t_big *datas)
{
	int		fd;

	datas->flag_pipe = 0;
	if (datas->flag_bracket == 0)
	{
		fd = open(argv[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		print_std_fd(datas->fd, fd);
		datas->fd = fd;
	}
	else
	{
		fd = open(argv[0], O_CREAT | O_WRONLY, 0644);
		close(fd);
	}
	ft_copy_arg(argv, datas);
}

void	exec_anglebracket_left(char **argv, t_big *datas)
{
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
	close(fd);
}

void	exec_anglebracket_left(char **argv, t_big *datas)
{
	int		fd;

	datas->flag_pipe = 0;
	fd = open(argv[0], O_RDONLY);
	if (fd < 0)
	{
		print_errors("minishellrose: No such file or directory");
		datas->quit = 1;
	}
	datas->fd = fd;
}

void	exec_double_anglebracket_right(char **argv, t_big *datas)
{
	int		fd;

	datas->flag_pipe = 0;
	fd = open(argv[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (datas->flag_bracket == 0)
	{
		print_std_fd(datas->fd, fd);
		datas->fd = fd;
	}
	else
	{
		fd = open(argv[0], O_CREAT | O_WRONLY, 0644);
		close(fd);
	}
	ft_copy_arg(argv, datas);
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
