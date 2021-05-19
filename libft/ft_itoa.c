/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 20:24:29 by gpetit            #+#    #+#             */
/*   Updated: 2020/12/28 16:13:34 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(long nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		count++;
	if (nb < 0)
	{
		nb = -nb;
		count++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(long nb)
{
	char	*stock;
	int		i;

	i = ft_size(nb);
	stock = malloc(sizeof(char) * (i + 1));
	if (!stock)
		return (NULL);
	stock[i--] = '\0';
	if (nb == 0)
	{
		stock[0] = '0';
		return (stock);
	}
	if (nb < 0)
	{
		nb = -nb;
		stock[0] = '-';
	}
	while (nb > 0)
	{
		stock[i] = ((nb % 10) + 48);
		nb = nb / 10;
		i--;
	}
	return (stock);
}

/*
** int		main()
**{
**	int i;
**	char *tab;
**
**	i = 8484;
**	tab = ft_itoa(i);
**	printf("Resultat = %s\n", tab);
**	return (0);
**}
*/
