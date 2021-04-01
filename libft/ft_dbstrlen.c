/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbstrlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:17:16 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/01 16:17:55 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_dbstrlen(char **str)
{
	int k;

	k = 0;
	while (str[k])
		k++;
	return (k);
}
