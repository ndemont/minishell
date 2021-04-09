/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:41:48 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/09 17:07:27 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env(t_big *data, char *var)
{
	int		i;
	int		pos;
	char	*ref;
	char	*value;

	i = 0;
	value = malloc(sizeof(char));
	value[0] = '\0';
	while (data->env[i])
	{
		pos = 0;
		while (data->env[i][pos] != '=')
			pos++;
		ref = ft_substr(data->env[i], 0, pos);
		if (!ft_strcmp(ref, var))
		{
			value = ft_substr(data->env[i], pos, ft_strlen(data->env[i]));
			break ;
		}
		i++;
	}
	return (value);
}