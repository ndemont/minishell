/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:31:47 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/06 11:52:04 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_std(int fd)
{
	char *line;

	//dup2(fd_out, STDOUT_FILENO);
	while (get_next_line(fd, &line))
		printf("%s\n", line);
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

void	exec_built_in(char *command, char **argv)
{
	(void)command;
	(void)argv;
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


void	exec_cmd(char *command, char **argv, int is_built_in, int *fd_out)
{
	int fd[2];
	pid_t pid1;

	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(*fd_out, STDIN_FILENO); // ?? attention peut etre mieux à l'exterieur
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		if (is_built_in == 1)
			exec_built_in(command, argv);
		else
			exec_binary(command, argv);
		close(*fd_out);
		exit(0);  //permet de fermer execve dans le fork après l'avoir RUN
	}
	waitpid(pid1, NULL, 0);
	dup2(fd[0], *fd_out);
	close(fd[1]);
	close(fd[0]);
}

void	executions(t_node **token, t_big *datas)
{
	int fd_out;
	int i;

	(void)datas;
	i = 0;
	fd_out = dup(STDIN_FILENO);
	if (!token[i]->command)
		exec_cmd(token[i]->builtin, token[i]->arg, 1, &fd_out); //Envoyer commande ou BUILTIN en FLAG
	else
		exec_cmd(token[i]->command, token[i]->arg, 0, &fd_out);
	i = 2;
	if (!token[i]->command)
		exec_cmd(token[i]->builtin, token[i]->arg, 1, &fd_out); //Envoyer commande ou BUILTIN en FLAG
	else
		exec_cmd(token[i]->command, token[i]->arg, 0, &fd_out);
	print_std(fd_out);
	close(fd_out);
}