/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:19:09 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/17 19:19:10 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**store_first_elem(char *env_elem)
{
	void	*content;
	t_list	**start;

	start = (t_list **)malloc(sizeof(t_list));
	if (!start)
		return (ERROR);
	content = fill_tmp(env_elem);
	if (!content)
	{
		free(start);
		return (ERROR);
	}
	*start = ft_lstnew(content);
	if (!(*start))
	{
		free(content);
		free(start);
		return (ERROR);
	}
	return (start);
}

int	store_others_elem(char *env_elem, t_list **start)
{
	t_list	*tmp;
	void	*content;

	content = fill_tmp(env_elem);
	if (!content)
		return (ERROR);
	tmp = ft_lstnew(content);
	if (!tmp)
	{
		free(content);
		return (ERROR);
	}
	ft_lstadd_back(start, tmp);
	return (SUCCESS);
}

t_var	*create_single_tmp(void)
{
	t_var	*tmp;

	tmp = (t_var *)malloc(sizeof(t_var));
	if (!tmp)
		return (ERROR);
	tmp->var = NULL;
	tmp->value = NULL;
	return (tmp);
}

void	free_elems_print_error(char **str, t_var **tmp)
{
	clean_free(str);
	free(*tmp);
	printi_stderr(0, strerror(errno), 0);
}

t_var	*fill_tmp(char *str)
{
	int		i;
	t_var	*tmp;

	i = 0;
	tmp = create_single_tmp();
	if (!tmp)
		return (ERROR);
	while (str[i] && str[i] != '=')
		i++;
	tmp->var = ft_substr(str, 0, i);
	if (!(tmp->var))
	{
		free(tmp);
		printi_stderr(0, strerror(errno), 0);
		return (ERROR);
	}
	if (str[i] == '=')
		i++;
	tmp->value = ft_substr(str, i, (ft_strlen(str) - i));
	if (!(tmp->value))
	{
		free_elems_print_error(&tmp->var, &tmp);
		return (ERROR);
	}
	return (tmp);
}
