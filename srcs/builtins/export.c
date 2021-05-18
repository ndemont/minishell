/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 19:15:06 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/06 11:28:55 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	non_conform_argument(char *arg)
{
	static char	error_str[] = "' not a valid identifier";
	char		*identifier;

	identifier = get_identifier(arg);
	identifier = ft_realloc(identifier, ft_strlen(identifier) + \
	ft_strlen(error_str) + 1);
	ft_strlcat(identifier, error_str, ft_strlen(identifier) + \
	ft_strlen(error_str) + 1);
	printi_stderr("export: '", identifier, 1);
	free(identifier);
	tcaps.ret = 1;
}

void	argument_without_equal(char *arg, t_big *datas)
{
	if (check_duplicate(*datas->hidden, arg) && \
	!check_duplicate(*datas->export, arg))
		add_hidden_to_env_export(arg, datas);
	else if (!check_duplicate(*datas->hidden, arg) && \
	!check_duplicate(*datas->export, arg))
		add_hidden_add_export(arg, datas);
}

void	argument_with_equal(char *arg, t_big *datas)
{
	if (!check_duplicate(*datas->hidden, arg))
		add_hidden_add_export_add_env(arg, datas);
	else
	{
		actualize_list(arg, *datas->hidden);
		if (check_duplicate(*datas->export, arg) && \
		!check_duplicate(*datas->env, arg))
			actualize_export_add_env(arg, datas);
		else if (check_duplicate(*datas->export, arg) && \
		check_duplicate(*datas->env, arg))
			actualize_export_actualize_env(arg, datas);
		else if (!check_duplicate(*datas->export, arg))
			add_hidden_to_env_export(arg, datas);
	}
}

void	treat_argument(char *arg, t_big *datas)
{
	if (!check_arg_conformity(arg))
		non_conform_argument(arg);
	else if (!ft_strchr(arg, '='))
		argument_without_equal(arg, datas);
	else if (ft_strchr(arg, '='))
		argument_with_equal(arg, datas);
}

int		ft_export(char **arg, t_big *datas)
{
	int		i;

	i = 1;
	if (!arg[i])
		print_export(datas->export);
	else
	{
		while (arg[i])
			treat_argument(arg[i++], datas);
	}
	*datas->export = ft_lst_sort(*datas->export, &cmp_list);
	return (tcaps.ret);
}
