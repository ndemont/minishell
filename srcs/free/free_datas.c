/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_datas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 19:36:04 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/19 15:28:05 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_datas(t_big *datas)
{
	if (datas)
	{
		if (datas->redirection_arg)
			free_double(datas->redirection_arg);
		if (datas && datas->file_name)
			free(datas->file_name);
		if (datas->env)
			free_list(datas->env);
		if (datas->export)
			free_list(datas->export);
		if (datas->hidden)
			free_list(datas->hidden);
		if (datas->history)
			free_history(datas->history);
		if (datas->root)
			free_tree(datas->root);
		if (datas->input)
			free(datas->input);
		if (datas->browse)
			free(datas->browse);
		if (g_tcaps.current_dir)
			clean_free(&g_tcaps.current_dir);
	}
	return (1);
}
