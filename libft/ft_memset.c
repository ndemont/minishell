/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:05:09 by gpetit            #+#    #+#             */
/*   Updated: 2020/12/27 14:29:38 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int a, size_t len)
{
	unsigned char	*ptr2;

	ptr2 = (unsigned char *)ptr;
	while (len > 0)
	{
		*ptr2 = (unsigned char)a;
		ptr2++;
		len--;
	}
	return (ptr);
}
/*
**int		main()
**{
**	char str[] = "hello World";
**
**	printf("%s\n", str);
**	ft_memset(str, '5', 5*sizeof(str[0]));
**	printf("%s\n", str);
**	return (0);
**}
*/
