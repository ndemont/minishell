/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 13:55:06 by gpetit            #+#    #+#             */
/*   Updated: 2021/02/11 13:56:47 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_is_in_sep(char *str, int i, char *charset)
{
	int	j;

	j = 0;
	while (charset[j])
	{
		if (str[i] == charset[j])
			return (1);
		j++;
	}
	return (0);
}

static int	ft_wordcount(char *str, char *charset)
{
	int	i;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (str[i])
	{
		if (!(ft_is_in_sep(str, i, charset)) \
		&& (ft_is_in_sep(str, i + 1, charset) || str[i + 1] == '\0'))
			wordcount++;
		i++;
	}
	return (wordcount);
}

static void	ft_fill_tab(char *tab, char *str, int i, int j)
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

char	**ft_splits(char *str, char *charset)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	tab = malloc(sizeof(char *) * (ft_wordcount(str, charset) + 1));
	if (!tab)
		return (NULL);
	while (str[i] && k < ft_wordcount(str, charset))
	{
		while (ft_is_in_sep(str, i, charset) && str[i])
			i++;
		j = i;
		while (!(ft_is_in_sep(str, i, charset)) && str[i])
			i++;
		tab[k] = malloc(sizeof(char) * ((i - j) + 1));
		if (!(tab[k]))
			return (NULL);
		ft_fill_tab(tab[k], str, i, j);
		k++;
	}
	tab[k] = 0;
	return (tab);
}
