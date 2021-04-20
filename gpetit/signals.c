/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 10:56:30 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/20 13:27:54 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
	write(1, "Hello World\n", 12);
	printf("SIGINT = %i\n", sig);
	kill(pid_t, sig);
}

int	main(void)
{
	signal(SIGINT, &sigint_handler);
	while (1)
		sleep(1);
	return (0);
}
