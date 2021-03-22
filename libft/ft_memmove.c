/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:14:25 by gpetit            #+#    #+#             */
/*   Updated: 2020/11/23 11:45:59 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	i = 0;
	ptr1 = (unsigned char *)src;
	ptr2 = (unsigned char *)dst;
	if (!dst && !src)
		return (NULL);
	if (ptr1 < ptr2)
	{
		while (i++ < len)
			ptr2[len - i] = ptr1[len - i];
		return (dst);
	}
	while (i < len)
	{
		ptr2[i] = ptr1[i];
		i++;
	}
	return (dst);
}
