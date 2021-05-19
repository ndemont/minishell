/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:55:30 by gpetit            #+#    #+#             */
/*   Updated: 2020/12/28 17:06:27 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_hexaconvertor(char *stock, unsigned long nb, unsigned long i)
{
	static char	rosetta[] = "0123456789abcdef";

	if (nb > 0)
		ft_hexaconvertor(stock, nb / 16, i - 1);
	if (i <= ft_strlen(stock))
		stock[i] = rosetta[nb % 16];
}

char	*ft_print_hexa(unsigned long nb)
{
	char			*stock;
	unsigned long	x;
	unsigned long	count;

	x = nb;
	count = 0;
	if (x == 0)
		count = 1;
	while (x > 0)
	{
		x = x / 16;
		count++;
	}
	stock = malloc(sizeof(char) * (count + 1));
	if (!stock)
		return (NULL);
	stock[count] = '\0';
	ft_hexaconvertor(stock, nb, count - 1);
	return (stock);
}
