/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:59:24 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/21 18:29:45 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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
	while(new && i < size)
	{
		new[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
	ptr = new;	
	return (ptr);
}

int	main(void)
{
	char *str;
	char str2[] = " World";

	str = malloc(sizeof(char) * 6);
	str[0] = 'h';
	str[1] = 'e';
	str[2] = 'l';
	str[3] = 'l';
	str[4] = 'o';
	str[5] = '\0';
	printf("[%s]\n", str);
	ft_realloc(str, ft_strlen(str) + ft_strlen(str2));
	ft_strlcat(str, str2, ft_strlen(str) + ft_strlen(str2));
	printf("[%s]\n", str);
	return (0);
}
