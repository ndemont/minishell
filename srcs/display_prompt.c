/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:02:15 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/28 14:20:57 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_prompt(void)
{
	write(STDOUT_FILENO, PURPLE, 7);
	write(STDOUT_FILENO, "minishellrose-v1$ ", 18);
	write(STDOUT_FILENO, RESET, 6);
	raw_mode();
	tcaps.line_lvl = 0;
	cursor_position();
	tcaps.c_start = tcaps.c_pos;
	tcaps.cursor_max += tcaps.c_start;
	normal_mode();
	return (1);
}

void	execute_line(int i, char **line, char *buf)
{
	*line = ft_realloc(*line, ft_strlen(*line) + 2);
	ft_strlcat(*line, buf, ft_strlen(*line) + 2);
	(*line)[i] = 0;
}

char *create_line(t_big *datas)
{
	int ret;
	char buf[7];
	char *line;
	int i;
	int j;
	int	non_print_flag;

	line = ft_strdup(""); //CONTROLLER MALLOC
	i = 0;
	ret = 0;
	ft_bzero(buf, 7);
	raw_mode();
	while (line[i] != '\n')
	{
		cursor_position();
		non_print_flag = 0;
		ft_bzero(buf, 7);
		if ((ret = read(STDIN_FILENO, buf, 7)) < 0)
			exit(1); //SORTIR CLEAN PLUS TARD
		if (tcaps.signal)
		{
			if (line)
				free(line);
			line = ft_strdup("");
			tcaps.signal = 0;
			i = 0;
		}
		if (ret == 0)
			break ;
		j = 0;
		while (buf[j])
		{
			if ((int)buf[j] == 10) //VERIFIER QU'AUCUN AUTRE COMMANDE NE POSSEDE \n dans son pattern
				break;
			else if (((int)buf[j] >= 0 && (int)buf[j] <= 31) || (int)buf[j] == 127)
				non_print_flag = 1;
			j++;
		}
		if (non_print_flag || tcaps.cursor_pos < i)
		{
			//DEVELOPMENT_MODE_print_sequence(buf);
			if (buf[0] == 10)
			{
				execute_line(i, &line, buf);
				break ;
			}
			do_the_right_thing(&i, buf, &line, datas);
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
			print_at_cursor(line[i]);
			//write(STDIN_FILENO, &line[i], 1);	
			i++;
			tcaps.cursor_pos = i;
		}
	}
	normal_mode();
 	ft_putchar('\n');
	return (line);
}

void	clean_datas(t_big *datas)
{
	if (datas->redirection_arg)
		free(datas->redirection_arg);
}

int	read_input(t_big *datas)
{
	char	*line;
	t_node	**token_tab;

	actualize_data(datas);
	line = NULL;
	datas->quit = 0;
	display_prompt();
	token_tab = 0;
	line = create_line(datas);
	if (!line)
		return (0);
	if (!line[0])
		return (1);
/* 	if (tcaps.signal)
		return (1); */
	save_history(line, datas);
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
	clean_datas(datas); //NECESSAIRE ?? DEMANDER A NAS
	return (1);
}
