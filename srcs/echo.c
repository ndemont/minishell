/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:31:28 by ndemont           #+#    #+#             */
/*   Updated: 2021/03/25 21:21:19 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!new)
		return(0);
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
	char	*var;
	char	*tmp;

	while (str[i] && str[i] != "\"")
	{
		tmp = new;
		if (str[i] != "$")
		{
			new = ft_strjoin(new, (char *)str[i]);
			i++;
		}
		else
		{
			var = ft_env(&i, str);
			if (!var)
				return (0);
			new = ft_strjoin(new, ft_env(&i, str));
		}
		free(tmp);
		if (!new)
			return (0);
	}
	if (str[i] == '\0')
		return (0);
	return (new);
}

static int	ft_parse_echo(char *arg, char *echo, int i)
{
	char *tmp;
	
	while (arg[i])
	{
		tmp = echo;
		while (arg[i] == ' ')
			i++;
		if (arg[i] == '"')
		{
			new = ft_quote_mark(i, arg);
			echo = ft_strjoin(echo, new);
			free(new);
		}
		else if (arg[i] == '$')
		{
			new = ft_env(i, arg);
			echo = ft_strjoin(echo, new);
			free(new);
		}
		else
			echo = ft_strjoin(echo, (char *)arg[i]);
		free(tmp);
		i++;
	}
	
}

int			ft_echo(char *arg, char *echo) /*add the general structure to the arguments*/
{
	int		i;
	int		option;
	char	*tmp;

	i = 0;
	option = 0;
	while (arg[i] == ' ')
		i++;
	if (arg[i] == '-' && arg[i + 1] == 'n')
		option = 1;
	ft_parse_echo(arg, echo, i);
	if (!option)
	{
		tmp = echo;
		echo = ft_strjoin(echo, "\n");
		free(tmp);
	}		
}
