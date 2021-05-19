/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:46:27 by gpetit            #+#    #+#             */
/*   Updated: 2020/12/27 15:39:48 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_trimable(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strim;
	int		a;
	int		z;
	int		k;
	int		len;

	if (!s1 || !set)
		return (NULL);
	a = 0;
	z = ft_strlen(s1);
	while (is_trimable(s1[a], set) && s1[a])
		a++;
	while (is_trimable(s1[z - 1], set))
		z--;
	len = z - a;
	if (len < 0)
		len = 0;
	strim = malloc(sizeof(char) * ((len) + 1));
	if (!strim)
		return (NULL);
	k = 0;
	while (a < z)
		strim[k++] = s1[a++];
	strim[k] = '\0';
	return (strim);
}
/*
**int		main(void)
**{
**	char const str[] = "\t   \n\n\n  \n\n\t    Hello \t  Please\n
**Trim me !\t\t\t\n  \t\t\t\t  ";
**	char set[] = " o";
**	char *result;
**
**	result = ft_strtrim(str, " \n\t");
**	printf("%s\n", result);
**	return (0);
**}
*/
