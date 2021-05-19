/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parents.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 23:41:41 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/18 23:49:05 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_parent(t_node *root, int n, t_big *datas, int side)
{
	(void)side;
	if (!datas->quit && n == 0 && root->command)
		exec_semicolon_cmd(root->command, root->arg, 0, datas);
	if (!datas->quit && n == 0 && root->builtin)
		g_tcaps.ret = exec_built_in(root->builtin, root->arg, datas);
}

void	pipe_parent(t_node *root, int n, t_big *datas, int side)
{
	(void)side;
	if (n == 1 && (root->command || root->builtin))
		exec_piped_cmd(root->command, root->builtin, root->arg, datas);
}

void	semicolon_parent(t_node *root, int n, t_big *datas, int side)
{
	(void)side;
	if (n == 5 && root->command)
		exec_semicolon_cmd(root->command, root->arg, 0, datas);
	if (n == 5 && root->builtin)
		exec_semicolon_cmd(root->builtin, root->arg, 1, datas);
	else if (n == 5)
		exec_semicolon_cmd(root->builtin, root->arg, 2, datas);
}

void	right_redir_parent(t_node *root, int n, t_big *datas, int side)
{
	if ((n == 2 || n == 3) && side == 1 && (root->command || root->builtin))
		redirections(n, root->arg, datas);
	if ((n == 2 || n == 3) && side == 2 && (root->command || root->builtin))
		exec_piped_cmd(root->command, root->builtin, root->arg, datas);
}

void	left_redir_parent(t_node *root, int n, t_big *datas, int side)
{
	if (n == 4 && side == 1)
		redirections(n, root->arg, datas);
	else if (n == 4 && side == 2 && (root->builtin || root->command))
		exec_piped_cmd(root->command, root->builtin, root->arg, datas);
}
