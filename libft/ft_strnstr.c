/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:04:03 by gpetit            #+#    #+#             */
/*   Updated: 2020/11/22 16:04:53 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hst, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*h;

	i = 0;
	h = (char *)hst;
	if (!(needle[i]))
		return (h);
	while (h[i] && i < len)
	{
		j = 0;
		while (needle[j] && h[i + j] == needle[j] && i + j < len)
			j++;
		if (!(needle[j]))
			return (h + i);
		i++;
	}
	return (NULL);
}
/*
**int		main()
**{
**	char str[] = "Hello World This is Me";
**	char needle[] = "This";
**	char *ptr;
**	char *ptr2;
**
**	ptr = ft_strnstr(str, needle, 30);
**	ptr2 = strnstr(str, needle, 30);
**	printf("MON STRN = %s\n", ptr);
**	printf("VRAI STRN = %s\n", ptr2);
**}
*/
