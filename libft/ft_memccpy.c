/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:50:03 by gpetit            #+#    #+#             */
/*   Updated: 2020/11/22 13:16:16 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n)
	{
		*(unsigned char *)dst = *(const unsigned char *)src;
		if (*(const unsigned char *)src == (unsigned char)c)
			return (dst + 1);
		dst++;
		src++;
		n--;
	}
	return (NULL);
}
