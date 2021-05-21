/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 23:40:03 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/21 11:42:41 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_std(int fd)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		ft_putstr(line);
		ft_putchar('\n');
		free(line);
		ret = get_next_line(fd, &line);
	}
	ft_putstr(line);
	free(line);
}

void	execute_tree(t_node *root, int parent, t_big *datas, int side)
{
	if (g_tcaps.exit)
	{
		if (root->left)
			execute_tree(root->left, root->type, datas, 1);
		if (root->right)
			execute_tree(root->right, root->type, datas, 2);
		if (datas->quit)
			return ;
		replace_variable(root, datas);
		if (parent != 2 && parent != 3 && parent != 4 && !root->type)
		{
			if (parent == 1)
				g_tcaps.ret = 0;
			root->arg = get_arguments(root, datas);
		}
		if (parent == 0 && root->arg && root->arg[0])
			no_parent(root, parent, datas, side);
		if (parent == 1 && root->arg && root->arg[0])
			pipe_parent(root, parent, datas, side);
		if ((parent == 2 || parent == 3) && root->arg && root->arg[0])
			right_redir_parent(root, parent, datas, side);
		if (parent == 4 && root->arg && root->arg[0])
			left_redir_parent(root, parent, datas, side);
		if (parent == 5 && root->arg && root->arg[0])
			semicolon_parent(root, parent, datas, side);
	}
}

void	executions(t_big *datas)
{
	int	i;

	i = 0;
	datas->flag_pipe = 0;
	datas->fd = dup(STDIN_FILENO);
	execute_tree(datas->root, 0, datas, 0);
	if (!g_tcaps.exit || datas->quit)
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
