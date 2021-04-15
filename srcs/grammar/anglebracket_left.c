/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anglebracket_left.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:10:57 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/15 14:11:29 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_file(char *path)
{
	int fd;
	int ret;
	char *line;

	fd = open(path, O_RDONLY);
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		ft_putstr_fd(line, 0);
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (ret != -1)
	{
		ft_putstr_fd(line, 0);
		free(line);
	}
	close(fd);
}

void	redirections(char *str, char c, char *path)
{
	if (c == '>')
		overwrite_file(str, path);
	else if (c == 'A') //'A' is for append and is quivalent to ">>"
		append_file(str, path);
	else if (c == '<')
	{	
		(void)str;
		redirect_file(path);
	}
}