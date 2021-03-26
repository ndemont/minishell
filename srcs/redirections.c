/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:23:19 by gpetit            #+#    #+#             */
/*   Updated: 2021/03/26 15:54:16 by gpetit           ###   ########.fr       */
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

void	append_file(char *str, char *path)
{
	int fd;

	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	ft_putstr_fd(str, fd);
	close(fd);
}

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
		ret = get_next_line(fd, &line);
	}
	if (ret != -1)
		ft_putstr_fd(line, 0);
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

/*int	main(int ac, char **av)
**{
**	(void)ac;
**	printf("%s\n", av[1]);
**	printf("%c\n", *(av[2]));
**	printf("%s\n", av[3]);
**	redirections(av[1], *av[2], av[3]);
**	return (0);
}*/
