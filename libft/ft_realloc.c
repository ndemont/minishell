/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:59:24 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/06 15:20:59 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	size_t	i;
	char	*new;

	i = 0;
	if (!ptr)
		return (ptr = malloc(size));
	if (!size)
		return (NULL);
	new = malloc(size);
	if (!new)
		return (0);
	while (new && ((char *)ptr)[i] && i < size)
	{
		new[i] = ((char *)ptr)[i];
		i++;
	}
	new[i] = 0;
	free(ptr);
	ptr = new;
	return (ptr);
}
