/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:31:47 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/06 11:34:16 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_std(int fd)
{
	char	*line;
	int 	ret;
	
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

char **path_array(char *command)
{
	char *tmp;
	char **paths;
	char **binaries;
	int k;

	k = 0;
	if ((tmp = getenv("PATH")) == NULL)
	{
		perror("PATH is invalid ");
		exit(0); //replace by custom exit fct that deallocate everything 
	}
	paths = ft_split(tmp, ':');
	if (!paths)
	{
		perror("ft_split failed ");
		exit(0); //replace by custom exit fct that deallocate everything 
	}
	tmp = ft_strjoin("/", command);
	binaries = (char **)malloc(sizeof(char *) * (ft_dbstrlen(paths) + 1));
	while (paths[k])
	{
		binaries[k] = ft_strjoin(paths[k], tmp);
		if (!binaries[k])
		{
			printf("k = %i\n", k);
			perror("strjoin_failed");
			exit (0); //replace by custom exit fct that deallocate everything 
		}
		k++;
	}
	binaries[k] = 0;
	free(tmp);
	free_double(paths);
	return (binaries);
}

char **mono_array(char *str)
{
	char **cmd;

	cmd = (char **)malloc(sizeof(char*) * 1);
	if (!cmd)
	{
		perror("Malloc failed in mono_array ");
		exit(0); //replace by custom exit fct
	}
	cmd[0] = ft_strdup(str);
	if (!cmd[0])
	{
		perror("Malloc failed in mono_array2 ");
		exit (0);
	}
	cmd[1] = 0;
	return (cmd);
}


char **build_array(char *command)
{
	char **cmd; 

	if (ft_strchr(command, '/'))
		cmd = mono_array(command);
	else
		cmd = path_array(command);
	return (cmd);
}

int		exec_built_in(char *command, char **argv, t_big *datas)
{
	int ret;

	if (!(ft_strcmp(command, "echo")))
		ret = ft_echo(argv, datas);
	if (!(ft_strcmp(command, "cd")))
		ret = ft_cd(argv, datas);
	if (!(ft_strcmp(command, "env")))
		ret = ft_env(argv, datas);
	if (!(ft_strcmp(command, "pwd")))
		ret = ft_pwd(datas);
	if (!(ft_strcmp(command, "export")))
		ret = ft_export(argv, datas);
	if (!(ft_strcmp(command, "unset")))
		ret = ft_unset(argv, datas);
	if (!(ft_strcmp(command, "exit")))
		ret = ft_exit(argv, datas);
	if(ft_strchr(command, '='))
		ret = ft_hidden(argv, datas);
	return (ret);
}

char	**build_array_env(t_list *lst)
{
	int size;
	int i;
	char *line;
	char **env;

	i = 0;
	size = ft_lstsize(lst);
	env = (char **)malloc(sizeof(char *) * (size + 1));
	while (lst)
	{
		line = ft_strjoin(((t_var *)(lst->content))->var, "=");
		line = ft_realloc(line, ft_strlen(line) + ft_strlen(((t_var *)(lst->content))->value) + 1);
		ft_strlcat(line, ((t_var *)(lst->content))->value, (ft_strlen(line) + ft_strlen(((t_var *)(lst->content))->value) + 1));
		env[i] = line;
		i++;
		lst = lst->next;
	}
	env[i] = 0;
	return (env);
}

void	exec_binary(char *command, char **argv, t_big *datas)
{
	char **cmd;
	char **env;
	int k;
	int ret;

	cmd = build_array(command);
	env = build_array_env(*datas->env);
 	k = 0;
	while (cmd[k] && ((ret = execve(cmd[k], argv, env)) == -1))
		k++;
	if (ret == -1)
	{
		tcaps.ret = RET_ERROR;
		printf("minishellrose: %s: command not found\n", command);
	}
	free_double(cmd);
	free_double(env);
}

void	execute_tree(t_node *root, int n, t_big *datas, int side)
{
	if (!datas->quit)
	{
		if (root->left)
			execute_tree(root->left, root->type, datas, 1);
		if (root->right)
			execute_tree(root->right, root->type, datas, 2);
		if (!datas->quit && n == 0 && root->command)
			exec_semicolon_cmd(root->command, root->arg, 0, datas);
		if (!datas->quit && n == 0 && root->builtin)
			exec_built_in(root->builtin, root->arg, datas);
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
	if (datas->flag_pipe)
		print_std(datas->fd);
	if (datas->flag_bracket)
	{
		print_std_fd(datas->fd, datas->fd_out);
		ft_putstr_fd("\n", datas->fd);
		close(datas->fd_out);
		datas->fd_out = STDOUT_FILENO;
	}
	close(datas->fd); //CAUTIOUS
}
