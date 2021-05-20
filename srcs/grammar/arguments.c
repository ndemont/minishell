/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 12:00:16 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/20 15:45:41 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_ambiguous_arg(char **argv, t_big *datas)
{
	if (argv && argv[0] && argv[0][0] && argv[0][1])
	{
		if (argv[0][0] == '"' && argv[0][1] == '$')
		{
			g_tcaps.ret = 1;
			datas->flag_bracket = 1;
			datas->fd_out = open(".hidden", O_CREAT |  O_WRONLY | O_TRUNC, 0644);
			return (printi_stderr(0, "ambiguous redirect", 1));
		}
	}
	return (1);
}

static int	count_len_total(char **argv, t_big *datas)
{
	int	len_new;
	int	len_old;

	len_new = 1;
	len_old = 0;
	if (argv)
	{
		while (argv[len_new])
			len_new++;
	}
	len_new--;
	if (!len_new)
		return (0);
	if (datas->redirection_arg)
	{
		while (datas->redirection_arg && datas->redirection_arg[len_old])
			len_old++;
	}
	return (len_old + len_new);
}

int	copy_old_args(t_big *datas, char **tmp)
{
	int	len;

	len = 0;
	while (tmp && tmp[len])
	{
		datas->redirection_arg[len] = ft_strdup(tmp[len]);
		if (!(datas->redirection_arg[len]))
		{
			printi_stderr(0, strerror(errno), 0);
			return (-1);
		}
		len++;
	}
	return (len);
}

int	copy_new_args(char **argv, t_big *datas, int len)
{
	int	i;

	i = 1;
	while (argv && argv[i])
	{
		datas->redirection_arg[len] = ft_strdup(argv[i]);
		if (!(datas->redirection_arg[len]))
			return (printi_stderr(0, strerror(errno), 0));
		len++;
		i++;
	}
	return (1);
}

int	ft_copy_arg(char **argv, t_big *datas)
{
	int		len;
	char	**tmp;

	len = count_len_total(argv, datas);
	if (!len)
		return (1);
	tmp = datas->redirection_arg;
	datas->redirection_arg = (char **)malloc(sizeof(char *) * (len + 1));
	if (!datas->redirection_arg)
		return (printi_stderr(0, strerror(errno), 0));
	datas->redirection_arg[len] = 0;
	len = copy_old_args(datas, tmp);
	if (len < 0)
		return (0);
	if (tmp)
		free(tmp);
	len = copy_new_args(argv, datas, len);
	if (!len)
		return (0);
	return (1);
}
