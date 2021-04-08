/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:17:43 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/08 18:47:27 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	int fd;
	char *line;

	fd = open("droma.txt", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		printf("%s\n", line);
	printf("%s", line);
	close(fd);
	return (0);
}
