/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:02:15 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/26 13:01:24 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_prompt(void)
{
	write(STDOUT_FILENO, PURPLE, 7);
	write(STDOUT_FILENO, "minishellrose-v1$ ", 18);
   	write(STDOUT_FILENO, RESET, 6);
	raw_mode();
	cursor_position();
	tcaps.c_start = tcaps.c_pos;
	normal_mode();
	return (1);
}

char *create_line(t_big *datas)
{
	int ret;
	char buf[4];
	char *line;
	int i;
	int j;
	int	non_print_flag;

	line = ft_strdup(""); //CONTROLLER MALLOC
	i = 0;
	ret = 0;
	buf[3] = 0;
	//cursor_position(); //UNDER RAW_MODE_FCT, IT CANNOT BE PRINTED
	raw_mode();
	while (line[i] != '\n')
	{
		cursor_position(); //UNDER RAW_MODE_FCT, IT CANNOT BE PRINTED
		non_print_flag = 0;
		if ((ret = read(STDIN_FILENO, buf, 4)) < 0)
			exit(1); //SORTIR CLEAN PLUS TARD
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
		if (non_print_flag)
		{
			//UTILE POUR CONTROLER SANS POURRIR OUTPUT
			//DEVELOPPMENT_MODE_print_sequence(buf);
			//
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
		}
	}
	normal_mode();
 	ft_putchar('\n');
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
	line = create_line(datas);
	if (!line)
		return (0);
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
	//free_datas(datas);
	return (1);
}
