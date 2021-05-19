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

int	non_conform_argument(char *arg)
{
	static char	error_str[] = "' not a valid identifier";
	char		*identifier;

	identifier = get_identifier(arg);
	if (!identifier)
		return (ERROR);
	identifier = ft_realloc(identifier, ft_strlen(identifier) + \
	ft_strlen(error_str) + 1);
	if (!identifier)
		return (printi_stderr(0, strerror(errno), 0));
	ft_strlcat(identifier, error_str, ft_strlen(identifier) + \
	ft_strlen(error_str) + 1);
	printi_stderr("export: '", identifier, 1);
	free(identifier);
	g_tcaps.ret = 1;
	return (SUCCESS);
}

int	argument_without_equal(char *arg, t_big *datas)
{
	int	ret;

	ret = SUCCESS;
	if (check_duplicate(*datas->hidden, arg) && \
	!check_duplicate(*datas->export, arg))
		ret = add_hidden_to_env_export(arg, datas);
	else if (!check_duplicate(*datas->hidden, arg) && \
	!check_duplicate(*datas->export, arg))
		ret = add_hidden_add_export(arg, datas);
	if (!ret)
		return (ERROR);
	else
		return (SUCCESS);
}

int	argument_with_equal(char *arg, t_big *datas)
{
	int	ret;
	int	ret_final;

	ret = check_duplicate(*datas->hidden, arg);
	ret_final = SUCCESS;
	if (ret == ERR)
		return (ERROR);
	if (!ret)
		ret_final = add_hidden_add_export_add_env(arg, datas);
	else
		ret_final = treat_list(arg, datas);
	if (!ret_final)
		return (ERROR);
	else
		return (SUCCESS);
}

int	treat_argument(char *arg, t_big *datas)
{
	int	ret;
	int	ret2;
	int	ret_final;

	ret_final = SUCCESS;
	ret = check_arg_conformity(arg);
	ret2 = ft_strchr(arg, '=');
	if (ret == BUILT_IN_FAILURE || ret2 == BUILT_IN_FAILURE)
		return (BUILT_IN_FAILURE);
	if (!ret)
		ret_final = non_conform_argument(arg);
	else if (!ret2)
		ret_final = argument_without_equal(arg, datas);
	else if (ret2 > 0)
		ret_final = argument_with_equal(arg, datas);
	if (!ret_final)
		return (ERROR);
	return (SUCCESS);
}

int	ft_export(char **arg, t_big *datas)
{
	int	i;
	int	ret;

	i = 1;
	if (!arg[i])
		print_export(datas->export);
	else
	{
		while (arg[i])
		{
			ret = treat_argument(arg[i++], datas);
			if (ret == BUILT_IN_FAILURE)
				return (BUILT_IN_FAILURE);
		}
	}
	*datas->export = ft_lst_sort(*datas->export, &cmp_list);
	return (g_tcaps.ret);
}
