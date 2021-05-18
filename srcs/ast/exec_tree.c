/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 23:40:03 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/18 14:57:22 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_std(int fd)
{
	char	*line;
	int		ret;

	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_putstr(line);
		ft_putchar('\n');
		free(line);
	}
	ft_putstr(line);
	free(line);
}

void	execute_tree(t_node *root, int n, t_big *datas, int side)
{
	if (tcaps.exit)
	{
		if (root->left)
			execute_tree(root->left, root->type, datas, 1);
		if (root->right)
			execute_tree(root->right, root->type, datas, 2);
		if (n != 2 && n != 3 && n != 4 && !root->type)
		{
			if (n == 1)
				tcaps.ret = 0;
			root->arg = get_arguments(root, datas);
			replace_variable(root, datas);
		}
		if (!datas->quit && n == 0 && root->command)
			exec_semicolon_cmd(root->command, root->arg, 0, datas);
		if (!datas->quit && n == 0 && root->builtin)
			tcaps.ret = exec_built_in(root->builtin, root->arg, datas);
		if (n == 1 && (root->command || root->builtin))
			exec_piped_cmd(root->command, root->builtin, root->arg, datas);
		if (n == 5 && root->command)
			exec_semicolon_cmd(root->command, root->arg, 0, datas);
		if (n == 5 && root->builtin)
			exec_semicolon_cmd(root->builtin, root->arg, 1, datas);
		else if (n == 5)
			exec_semicolon_cmd(root->builtin, root->arg, 2, datas);
		if ((n == 2 || n == 3) && side == 1 && (root->command || root->builtin))
			redirections(n, root->arg, datas);
		else if ((n == 2 || n == 3) && side == 2 && (root->command || root->builtin))
			exec_piped_cmd(root->command, root->builtin, root->arg, datas);
		else if (n == 4 && side == 1)
			redirections(n, root->arg, datas);
		else if (n == 4 && side == 2 && (root->builtin || root->command))
			exec_piped_cmd(root->command, root->builtin, root->arg, datas);
	}
}

void	executions(t_big *datas)
{
	int i;

	i = 0;
	datas->flag_pipe = 0;
	datas->fd = dup(STDIN_FILENO);
	execute_tree(datas->root, 0, datas, 0);
	if (!tcaps.ret)
		return ;
	if (datas->flag_pipe)
		print_std(datas->fd);
	if (datas->flag_bracket)
	{
		print_std_fd(datas->fd, datas->fd_out);
		ft_putstr_fd("\n", datas->fd);
		close(datas->fd_out);
		datas->fd_out = STDOUT_FILENO;
	}
	close(datas->fd);
}
