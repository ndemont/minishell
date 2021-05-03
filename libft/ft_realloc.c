/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:59:24 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/22 11:30:09 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	size_t i;
	char *new;

	i = 0;
	if (!ptr)
		return (ptr = malloc(size));
	if (!size)
		return (NULL);
	new = malloc(size);
	while (new && ((char *)ptr)[i] && i < size)
	{
		new[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
	ptr = new;	
	return (ptr);
}

