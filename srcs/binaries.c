/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:31:47 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/09 19:33:29 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_std(int fd)
{
	char *line;

	while (get_next_line(fd, &line) > 0)
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

void	exec_built_in(char *command, char **argv, t_big *datas)
{
	if (!(ft_strcmp(command, "echo")))
		ft_echo(argv, datas);
	if (!(ft_strcmp(command, "cd")))
		ft_cd(argv, datas);
	if (!(ft_strcmp(command, "env")))
		ft_env(datas);
	return;
}

void	exec_binary(char *command, char **argv)
{
	char **cmd;
	int k;
	int ret;

	cmd = build_array(command);
 	k = 0;
	while (cmd[k] && ((ret = execve(cmd[k], argv, NULL)) == -1))
		k++;
	if (ret == -1)
	{
		write(1, "minishellrose: ", 15);
		ft_putstr(command);
		write(1, ": command not found\n", 20);
	}
	free_double(cmd);
}

void	exec_piped_cmd(char *command, char **argv, int is_built_in, t_big *datas)
{
	int fd[2];
	pid_t pid1;

	datas->flag_pipe = 1;
	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(datas->fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		if (is_built_in == 1)
			exec_built_in(command, argv, datas);
		else
			exec_binary(command, argv);
		close(datas->fd);
		exit(0);  //permet de fermer execve dans le fork après l'avoir RUN
	}
	waitpid(pid1, NULL, 0);
	dup2(fd[0], datas->fd);
	close(fd[1]);
	close(fd[0]);
}

void	execute_tree(t_node *root, int n, t_big *datas)
{
	if (root->left)
		execute_tree(root->left, root->type, datas);
	if (root->right)
		execute_tree(root->right, root->type, datas);
	if (n == 1 && root->command)
		exec_piped_cmd(root->command, root->arg, 0, datas); //RAjOUTER FD_OUT
	if (n == 1 && root->builtin)
		exec_piped_cmd(root->builtin, root->arg, 1, datas);
	if (n == 0 && root->builtin)
		exec_built_in(root->builtin, root->arg, datas);
	if (n == 0 && root->command)
		exec_piped_cmd(root->command, root->arg, 0, datas);
}

void	executions(t_big *datas)
{
	int i;

	i = 0;
	datas->flag_pipe = 0;
	datas->fd = dup(STDIN_FILENO);
	execute_tree(datas->root, 0, datas);
	if (datas->flag_pipe)
		print_std(datas->fd);
	close(datas->fd);
}
