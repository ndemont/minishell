/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:14:14 by gpetit            #+#    #+#             */
/*   Updated: 2021/03/31 17:31:08 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char *cmd;
	int pid;
	int	status;

	write(1, "entree", 6);

	(void)ac;
	pid = fork();
	if (pid == 0)
	{
		cmd = ft_strjoin("/bin/", av[1]);
		execve(cmd, av + 1, env);
	}
	else
	{
		wait(&status);
	}

	write(1, "sortie", 6);


	return (0);
}
