/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:02:15 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/11 12:13:12 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_prompt(void)
{
	write(STDOUT_FILENO, PURPLE, 7);
	write(STDOUT_FILENO, "minishellrose$ ", 15);
	write(STDOUT_FILENO, RESET, 6);
	raw_mode();
	cursor_position();
	tcaps.line_lvl = 0;
	tcaps.cursor_lvl = 0;
	tcaps.c_start = tcaps.c_pos;
	tcaps.cursor_max = tcaps.c_start;
	tcaps.cursor_pos = 0;
	normal_mode();
	return (1);
}

int		execute_line(int i, char **line, char *buf)
{
	if (!(*line = ft_realloc(*line, ft_strlen(*line) + 2)))
		return (0);
	ft_strlcat(*line, buf, ft_strlen(*line) + 2);
	(*line)[i] = 0;
	return (1);
}

char *create_line(t_big *datas)
{
	int		ret;
	char	buf[7];
	char	*line;
	int		i;
	int		j;
	int		non_print_flag;

	if (!(line = ft_strdup("")))
		return (0);
	i = 0;
	ret = 0;
	raw_mode();
	cursor_position();
	while (line[i] != '\n')
	{
		non_print_flag = 0;
		ft_bzero(buf, 7);
		if ((ret = read(STDIN_FILENO, buf, 6)) < 0)
			return (0);
		if (tcaps.signal)
		{
			if (line)
				free(line);
			if (!(line = ft_strdup("")))
				return (0);
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
		if 	(buf[0] != 27 || buf[1] != 91 || (buf[2] != 65 && buf[2] != 66))
			datas->flag_history = 0;
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
			i++;
			tcaps.cursor_pos = i;
		}
	}
	normal_mode();
 	ft_putchar('\n');
	return (line);
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
	if (!line && tcaps.exit)
		return (0);
	else if ((!line && !tcaps.exit) || !line[0])
		return (1);
	save_history(line, datas);
	token_tab = ft_lexer(line);
	if (!token_tab && tcaps.exit)
		return (0);
	else if (!token_tab && !tcaps.exit)
		return (1);
	if (!ft_builtin_parser(token_tab))
	{
		free_tokens(token_tab);
		return (0);
	}
	tree(token_tab, datas);
	executions(datas);
	clean_datas(datas);
	return (1);
}
