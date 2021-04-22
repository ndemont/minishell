/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:02:15 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/21 15:31:13 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_prompt(void)
{
	write(1, PURPLE, 7);
	write(1, "minishellrose-v1$ ", 18);
   	write(1, RESET, 6);
	return (1);
}

char *create_line(void)
{
	int ret;
	char buf[4];
	char *line;
	int i;
	int j;
	int	non_print_flag;
	struct termios term;
	struct termios original;

	line = ft_strdup(""); //CONTROLLER MALLOC
	i = 0;
	ret = 0;
	tcgetattr(STDIN_FILENO, &original);
	term = original;
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	int fd = open("droma.txt", O_APPEND | O_TRUNC | O_WRONLY | O_CREAT, 0644);
	while (line[i] != '\n')
	{
		non_print_flag = 0;
		if ((ret = read(STDIN_FILENO, buf, 4)) < 0)
			exit(1); //SORTIR CLEAN PLUS TARD
		ft_putnbr(ft_strlen(buf));
		if (ret == 0)
			break ;
		j = 0;
		while (buf[j])
		{
			if ((int)buf[j] == 10)
				break;
			else if (((int)buf[j] >= 0 && (int)buf[j] <= 31) || (int)buf[j] == 127)
				non_print_flag = 1;
			j++;
		}
		if (non_print_flag)
		{
			j = 0;
			while (buf[j])
			{
				printf("[%d] ", (int)buf[j]);
				j++;
			}
			printf(" | ");
			//ft_putstr("here");
			/* 		j = 0;
			while (buf[j])
			{
				dprintf(fd, "[%d] ", (int)buf[j]);
				j++;
			}
			dprintf(fd, " | "); */
		}
		else
		{
			line = ft_realloc(line, ft_strlen(line) + 1 + 1);
			ft_strlcat(line, buf, ft_strlen(line) + 2);
			if (buf[0] != '\n')
			{	
				line[i] = buf[0];
				line[i + 1] = 0;
			}
			else
			{
				line[i] = 0;
				break ;
			}
			write(STDIN_FILENO, &line[i], 1);	
			i++;
		}
	}
 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
 	ft_putchar('\n');
	 			close(fd);
	return (line);
}

int	read_input(t_big *datas)
{
	//int		ret;
	char	*line;
	t_node	**token_tab;

	actualize_data(datas);
	line = NULL;
	datas->quit = 0;
	display_prompt();
	token_tab = 0;
	line = create_line();
	if (!line)
		return (0);
	token_tab = ft_lexer(line);
	if (!(token_tab ))
		return (0);
	if (!ft_builtin_parser(token_tab))
		return (0);
	tree(token_tab, datas);
	printf("EXECUTION");
	printf("\n-----\n");
	executions(datas);
	//ret = 0;
	//free_tokens(token_tab);
	//free_datas(datas);
	return (1);
}
