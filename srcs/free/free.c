/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:19:05 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/01 13:39:52 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_node **tokens)
{
	int i;
	int j;

	i = 0;
	if (tokens)
	{
		while (tokens[i])
		{
			if (tokens[i]->input)
				free(tokens[i]->input);
			if (tokens[i]->ret)
				free(tokens[i]->ret);
			if (tokens[i]->arg)
			{
				j = 0;
				while (tokens[i]->arg[j])
				{
					free(tokens[i]->arg[j]);
					j++;
				}
				free(tokens[i]->arg);
			}
			free(tokens[i]);
			i++;
		}
		free(tokens);
	}
}

void	free_list(t_list **list)
{
	t_list *tmp;
	t_list *elem;

	if (list)
	{
		elem = *list;
		while (elem)
		{
			if (elem->content)
			{
				if (((t_var *)elem->content)->var)
				{
					free(((t_var *)elem->content)->var);
					((t_var *)elem->content)->var = 0;
				}
				if (((t_var *)elem->content)->value)
				{
					free(((t_var *)elem->content)->value);
					((t_var *)elem->content)->value = 0;
				}
				free(elem->content);
				elem->content = 0;
			}
			tmp = elem;
			elem = elem->next;
			free(tmp);
			tmp = 0;
		}
		free(list);
		list = 0;
	}
}

void	free_tab_arg(char **tab)
{
	int i;
	int j;

	i = 0;
	while (tab[i])
	{
		free(tab[i])
		tab[i] = 0;
		i++;
	}
}

void	free_tree(t_node *root)
{
	if (root->left)
	{
		free_tree(root->left);
		free(root->left);
		root->left = 0;
	}
	if (root->right)
	{
		free_tree(root->right);
		free(root->right);
		root->right = 0;
	}
	if (root->input)
	{
		free(root->input);
		root->input = 0;
	}
	if (root->arg)
	{
		free_tab_arg(root->arg);
		free(root->arg);
		root->arg = 0;
	}
	if (root->ret)
	{
		free(root->ret);
		root->ret = 0;
	}
	if (root->builtin)
	{
		free(root->builtin);
		root->builtin = 0;
	}
	if (root->command)
	{
		free(root->command);
		root->command = 0;
	}
}

void	free_datas(t_big *datas)
{
	if (datas)
	{
		if (datas->env)
			free_list(datas->env);
		if (datas->export)
			free_list(datas->export);
		if (datas->hidden)
			free_list(datas->hidden);
		if (datas->root)
			free_tree(datas->root);
		free(datas);
		datas = 0;
	}
}
