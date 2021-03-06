/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:19:05 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/19 11:31:22 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_node **tokens)
{
	int	i;

	i = 0;
	if (tokens)
	{
		while (tokens[i])
		{
			if (tokens[i]->input)
				clean_free(&tokens[i]->input);
			if (tokens[i]->arg)
			{
				free_arg(tokens[i]->arg);
				free(tokens[i]->arg);
				tokens[i]->arg = 0;
			}
			if (tokens[i]->builtin)
				clean_free(&tokens[i]->builtin);
			if (tokens[i]->command)
				clean_free(&tokens[i]->command);
			free(tokens[i]);
			i++;
		}
		free(tokens);
		tokens = 0;
	}
}

void	free_list(t_list **list)
{
	t_list	*tmp;
	t_list	*elem;

	if (list)
	{
		elem = *list;
		while (elem)
		{
			if (elem->content)
			{
				if (((t_var *)elem->content)->var)
					clean_free(&(((t_var *)elem->content)->var));
				if (((t_var *)elem->content)->value)
					clean_free(&(((t_var *)elem->content)->value));
				free(elem->content);
			}
			tmp = elem;
			elem = elem->next;
			free(tmp);
		}
		free(list);
	}
}

void	free_history(t_history **list)
{
	t_history	*tmp;
	t_history	*del;

	tmp = *list;
	while (tmp)
	{
		del = tmp;
		if (del->command)
			free(del->command);
		tmp = tmp->next;
		free(del);
	}
	if (*list)
		free(list);
}

void	clean_datas(t_big *datas)
{
	if (datas->redirection_arg)
		free_double(datas->redirection_arg);
	if (datas && datas->file_name)
		free(datas->file_name);
	if (datas->root)
		free_tree(datas->root);
	clean_free(&datas->input);
	clean_free(&datas->browse);
}
