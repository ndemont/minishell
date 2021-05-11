/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:10:15 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/11 11:25:35 by ndemont          ###   ########.fr       */
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
	if (line)
		free(line);
	line = 0;
}

void	ft_copy_arg(char **argv, t_big *datas)
{
	int		len_new;
	int		len_old;
	int		len_total;
	char	**tmp;
	
	len_new = 1;
	while (argv && argv[len_new])
		len_new++;
	len_new--;
	if (!len_new)
		return ;
	len_old = 0;
	while (datas->redirection_arg && datas->redirection_arg[len_old])
		len_old++;
	len_total  = len_old + len_new;
	tmp = datas->redirection_arg;
	datas->redirection_arg = (char **)malloc(sizeof(char *) * (len_total + 1));
	datas->redirection_arg[len_total] = 0;
	len_new = 0;
	while (len_new < len_old)
	{
		datas->redirection_arg[len_new] = ft_strdup(tmp[len_new]);
		len_new++;
	}
	len_new = 1;
	while (len_old < len_total)
	{
		datas->redirection_arg[len_old] = ft_strdup(argv[len_new]);
		len_new++;
		len_old++;
	}
	if (tmp)
		free(tmp);
}

void	exec_anglebracket_right(char **argv, t_big *datas)
{
	datas->flag_pipe = 0;
	datas->flag_left_bracket = 1;
	if (datas->fd_out != STDOUT_FILENO)
		close(datas->fd_out);
	datas->fd_out = open(argv[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_copy_arg(argv, datas);
	datas->file_name = ft_strdup(argv[0]);
	datas->flag_bracket = 1;
}

void	exec_anglebracket_left(char **argv, t_big *datas)
{
	int	fd;

	datas->flag_pipe = 0;
	printf("file name = %s\n", argv[0]);
	fd = open(argv[0], O_RDONLY);
	printf("fd = %d\n", fd);
	if (fd < 0)
	{
		printf("minishellrose: %s: No such file or directory\n", argv[0]);
		tcaps.ret = 1;
		datas->quit = 1;
	}
	if (datas->flag_left_bracket == 0)
		datas->fd = fd;
}

void	exec_double_anglebracket_right(char **argv, t_big *datas)
{
	datas->flag_pipe = 0;
	datas->flag_left_bracket = 1;
	if (datas->fd_out != STDOUT_FILENO)
		close(datas->fd_out);
	datas->fd_out = open(argv[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	ft_copy_arg(argv, datas);
	datas->file_name = ft_strdup(argv[0]);
	datas->flag_bracket = 1;
}

void	redirections(int type, char **argv, t_big *datas)
{
	if (type == 2)
		exec_double_anglebracket_right(argv, datas);
	else if (type == 3)
		exec_anglebracket_right(argv, datas);
	else if (type == 4)
		exec_anglebracket_left(argv, datas);
}