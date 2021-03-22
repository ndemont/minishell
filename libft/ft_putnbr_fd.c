/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:27:26 by gpetit            #+#    #+#             */
/*   Updated: 2020/11/20 10:59:17 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = (long)n;
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar_fd('-', fd);
	}
	if (nb >= 0 && nb <= 9)
		ft_putchar_fd(nb + 48, fd);
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd((nb % 10) + 48, fd);
	}
}
