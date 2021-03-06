/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:33:17 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/01 17:40:49 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_double(char **arr)
{
	int	k;

	k = 0;
	while (arr && arr[k])
	{
		free(arr[k]);
		k++;
	}
	if (arr)
		free(arr);
}
