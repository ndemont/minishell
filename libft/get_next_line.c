/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:44:21 by gpetit            #+#    #+#             */
/*   Updated: 2021/03/26 14:23:50 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strchr2(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr != c)
	{
		if (*ptr == '\0')
			return (NULL);
		ptr++;
	}
	return (ptr);
}

static void	ft_isolator(char **stock, char **line)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while ((*stock)[i] != '\n' && (*stock)[i] != '\0')
		i++;
	*line = ft_substr(*stock, 0, i);
	if (i + 1 > ft_strlen(*stock))
	{
		free(*stock);
		*stock = NULL;
	}
	else
	{
		tmp = ft_substr(*stock, i + 1, ft_strlen(*stock));
		free(*stock);
		*stock = ft_strdup(tmp);
		free(tmp);
	}
}

static int	ft_fork(char **stock, char **line, ssize_t by)
{
	if (by < 0)
	{
		free(*stock);
		*stock = NULL;
		return (-1);
	}
	else if (by == 0 && !*stock)
	{
		*line = ft_strdup("");
		return (0);
	}
	else if (!(ft_strchr2(*stock, '\n')))
	{
		*line = ft_strdup(*stock);
		free(*stock);
		*stock = NULL;
		return (0);
	}
	else
	{
		ft_isolator(stock, line);
		return (1);
	}
}

int	get_next_line(int fd, char **line)
{
	ssize_t		by;
	char		buff[BUFFER_SIZE + 1];
	static char	*stock[256];
	char		*temp;

	if (fd < 0 || fd > 256 || !line || BUFFER_SIZE < 1)
		return (-1);
	by = read(fd, buff, BUFFER_SIZE);
	while (by > 0)
	{
		buff[by] = '\0';
		if (!(stock[fd]))
			stock[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strdup(stock[fd]);
			free(stock[fd]);
			stock[fd] = ft_strjoin(temp, buff);
			free(temp);
		}
		if (ft_strchr2(stock[fd], '\n'))
			break ;
		by = read(fd, buff, BUFFER_SIZE);
	}
	return (ft_fork(&(stock[fd]), line, by));
}
