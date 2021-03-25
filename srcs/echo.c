/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:31:28 by ndemont           #+#    #+#             */
/*   Updated: 2021/03/25 19:13:06 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_split(char **split)
{
	int i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	*ft_env(int *i, char *str) /*add the general structure to the arguments*/
{
	char	*new;
	int		count;
	int		j;

	new = 0;
	count = i;
	while (str[count] != ' ')
		count++;
	new = malloc(sizeof(char) * (count + 1));
	new[count] = 0;
	j = 0;
	while (*i < count)
	{
		new[j] = str[*i];
		j++;
		*i = *i + 1;
	}
	//browse the env to find a corresponding variable
	//
	//if there is, itoa the value and join it to new
	// else no join
	return (new);
}

static char	*ft_quote_mark(int i, char *str) /*add the general structure to the arguments*/
{
	char	*new;

	while (str[i] && str[i] != "\"")
	{
		if (str[i] != "$")
		{
			new = ft_strjoin(new, (char *)str[i]);
			i++;
		}
		else
		{
			new = ft_strjoin(new, ft_env(&i, str));
		}
	}
	if (str[i] == '\0')
		return (0);
	return (new);
}

int			ft_echo(char *str, char *echo) /*add the general structure to the arguments*/
{
	int		i;
	int		option;
	char		*new;
	char		*tmp;

	i = 0;
	option = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' && str[i + 1] == 'n')
		option = 1;
	while (str[i])
	{
		tmp = echo;
		while (str[i] == ' ')
			i++;
		if (str[i] == '"')
		{
			new = ft_quote_mark(i, str);
			echo = ft_strjoin(echo, new);
			free(new);
		}
		else if (str[i] == '$')
		{
			new = ft_env(i, str);
			echo = ft_strjoin(echo, new);
			free(new);
		}
		else
			echo = ft_strjoin(echo, (char *)str[i]);
		free(tmp);
		i++;
	}
	free_split(split);
	if (!option)
		echo = ft_strjoin(echo, "\n");
}
