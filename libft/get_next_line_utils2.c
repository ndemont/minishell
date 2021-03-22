/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 12:30:43 by gpetit            #+#    #+#             */
/*   Updated: 2020/12/28 12:31:56 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_fill(char *dst, char const *s, int *i)
{
	int	j;

	j = 0;
	while (s[j])
	{
		dst[*i] = s[j];
		j++;
		(*i)++;
	}
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	ft_fill(dst, s1, &i);
	ft_fill(dst, s2, &i);
	dst[i] = '\0';
	return (dst);
}
