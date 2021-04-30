/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:27:45 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/30 11:30:32 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_arg(char *input, int *i)
{
	char	*arg;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	int		j;

	arg = malloc(sizeof(char));
	arg[0] = '\0';
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		*i = *i + 1;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t')
	{
		j = *i;
		while (input[*i] && input[*i] != ' ' && input[*i] != '\'' && input[*i] != '"' && input[*i] != '\t' && input[*i] != '\\')
			*i = *i + 1;
		tmp1 = arg;
		if (input[*i] == '\\' && input[*i + 1])
		{
			*i = *i + 1;
			tmp2 = ft_substr(input, j, *i - j - 1);
			tmp4 = ft_substr(input, *i, 1);
			tmp2 = ft_strjoin(tmp2, tmp4);
			*i = *i + 1;
		}
		else if (input[*i] == '\\' && !input[*i + 1])
			print_errors("minishellrose: missing char at end of line");
		else if (input[j] == '\'')
		{
			tmp2 = get_quote(input, i, &j);
			if (!tmp2)
				print_errors(strerror(errno));
		}
		else if (input[j] == '\"')
		{
			tmp2 = get_quote(input, i, &j);
			if (!tmp2)
				print_errors(strerror(errno));
			if (tmp2[0] == '$')
			{
				tmp3 = tmp2;
				tmp2 = malloc(sizeof(char) * (ft_strlen(tmp3) + 3));
				tmp2 = ft_strjoin("\"", tmp3);
				tmp2 = ft_strjoin(tmp2, "\"");
				printf("tmp2 = [%s]\n", tmp2);
			}
		}
		else
		{
			tmp2 = ft_substr(input, j, *i - j);
			if (!tmp2)
				print_errors(strerror(errno));
			if (tmp2[0] == '$')
			{
				tmp3 = tmp2;
				tmp2 = malloc(sizeof(char) * (ft_strlen(tmp3) + 3));
				tmp2 = ft_strjoin("\"", tmp3);
				tmp2 = ft_strjoin(tmp2, "\"");
			}
		}
		arg = ft_strjoin(tmp1, tmp2);
		free(tmp1);
		free(tmp2);
	}
	return (arg);
}

int			count_arg(char *input)
{
	int count;
	int	newword;
	int i;

	count = 0;
	i = 0;
	if (!input[0])
		return (0);
	while (input[i])
	{
		newword = 0;
		if (!i)
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
				i++;
		else
		{
			while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			{
				if (!newword)
					newword = 1;
				i++;
			}
			if (input[i])
				count += newword;
		}
		if (!input[i])
			break ;
		while (input[i] && input[i] != ' ' && input[i] != '\'' && input[i] != '"' && input[i] != '\t' && input[i] != '\\')
			i++;
		if (input[i] == '\\' && input[i + 1])
			i += 2;
		else if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'')
				i++;
			i++;
		}
		else if (input[i] == '"')
		{
			i++;
			while (input[i] != '"')
				i++;
			i++;
		}
		else if (!input[i])
			break ;
	}
	count++;
	return (count);
}
