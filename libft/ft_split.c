/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:04:12 by gpetit            #+#    #+#             */
/*   Updated: 2020/12/27 16:06:17 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char c, char d)
{
	if (c == d)
		return (1);
	else
		return (0);
}

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!(is_sep(s[i], c)) && ((is_sep(s[i + 1], c)) || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void	ft_fill_tab(char *tab, const char *str, int i, int j)
{
	int	r;

	r = 0;
	while (j < i)
	{
		tab[r] = str[j];
		j++;
		r++;
	}
	tab[r] = '\0';
}

char	*ft_split2(char const *s, char c, int *i, int *j)
{
	char	*tab;

	while (is_sep(s[*i], c) && s[*i])
		(*i)++;
	*j = *i;
	while ((!(is_sep(s[*i], c))) && s[*i])
		(*i)++;
	tab = malloc(sizeof(char) * ((*i - *j) + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[i] && k < count_words(s, c))
	{
		tab[k] = ft_split2(s, c, &i, &j);
		if (!(tab[k]))
			return (NULL);
		ft_fill_tab(tab[k], s, i, j);
		k++;
	}
	tab[k] = 0;
	return (tab);
}
