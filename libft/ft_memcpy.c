/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:34:49 by gpetit            #+#    #+#             */
/*   Updated: 2020/12/27 14:29:16 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ptr;

	ptr = dst;
	if (!src && !dst)
		return (NULL);
	while (n)
	{
		*(unsigned char *)dst = *(const unsigned char *)src;
		dst++;
		src++;
		n--;
	}
	return (ptr);
}
