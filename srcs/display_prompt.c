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
	char buf[1];
	char *line;
	char *tmp;
	int i;
	struct termios term;
	struct termios original;

	line = ft_strdup(""); //CONTROLLER MALLOC
	i = 0;
	ret = 0;
	tcgetattr(STDIN_FILENO, &original);
	term = original;
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	while (line[i] != '\n')
	{
		if ((ret = read(STDIN_FILENO, buf, 1)) < 0)
			exit(1); //SORTIR CLEAN PLUS TARD
		if (ret == 0)
			break ;
		tmp = line;
		line = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 2));
		strcpy(line, tmp); //ATTENTION, METTRE VRAIE FONCTION FT_STRCPY
		free(tmp);
		if (buf[0] != '\n')
		{	
			line[i] = buf[0];
			line[i + 1] = '\0';
		}
		else
		{
			line[i] = 0;
			break ;
		}
		write(STDIN_FILENO, &line[i], 1);	
		i++;
	}
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
	ft_putchar('\n');
	return (line);
}

int	read_input(t_big *datas)
{
	//int		ret;
	char	*line;
	t_node	**token_tab;

	init_data(datas);
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
