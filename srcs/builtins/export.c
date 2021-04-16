/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 19:15:06 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/14 14:11:17 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_plus_left(char *line)
{
	int i;
	char **str;

	i = 0;
	str = ft_split_on_equal(line);
	while (str[0] && str[0][i])
	{
		if (str[0][i] == '+')
			return (1);
		i++;
	}
	return (0);
	free_double(str);
}

int 	check_arg_conformity(char *line)
{
	int i;
	char **str;
	char *tmp;

	i = 0;
	str = ft_split_on_equal(line);
	tmp = str[0];
	if (ft_isdigit(tmp[0]))
		return (0);
	while (tmp[i])
	{
		if (!ft_isalnum(tmp[i]) && tmp != '_' && tmp != '+' && tmp != '\\')
			return (0);
		i++;
	}
	return (1);
	free_double(str);
}

int		check_plus_conformity(char *line)
{
	int i;
	char **str;

	i = 0;
	str = ft_split_on_equal(line);
	while (str[0] && str[0][i])
	{
		if (str[0][i] == '+' && i != (int)(ft_strlen(str[0]) - 1))
			return (0);
		i++;
	}
	return (1);
	free_double(str);
}

int		check_duplicate(t_list *list, char *ref)
{
	t_list	*tmp;
	int		count;
	char *str;
	int i;

 	i = 0;
	while (ref[i] && ref[i] != '=')
		i++;
	str = ft_substr(ref, 0, i);
	tmp = list;
	count = 0;
	while (tmp)
	{
		if (!ft_strcmp(((t_var *)tmp->content)->var, str))
		{
			free(str);
			return (1);
		}
		tmp = tmp->next;
		count++;
	}
	free(str);
	return (0);
}

//Si EXPORT sans égalité et que doublon apparait dans liste cachée alors --> actualisation de export et Env
void	add_hidden_to_env_export(char *line, t_big *datas) 
{
	t_list *hidden;
	t_list *tmp;
	t_var *content;
	t_var *content2;

	hidden = *datas->hidden;
	while (hidden && ft_strcmp(line, ((t_var *)hidden->content)->var))
		hidden = hidden->next;
	content = (t_var *)malloc(sizeof(t_var));
	content->var = ft_strdup(((t_var *)hidden->content)->var);
	content->value = ft_strdup(((t_var *)hidden->content)->value);
	content2 = (t_var *)malloc(sizeof(t_var));
	content2->var = ft_strdup(((t_var *)hidden->content)->var);
	content2->value = ft_strdup(((t_var *)hidden->content)->value);
	tmp = ft_lstnew(content);
	ft_lstadd_back(datas->export, tmp);
	tmp = ft_lstnew(content2);
	ft_lstadd_back(datas->env, tmp);
}

void	actualize_export_add_env(char *line, t_big *datas)
{
	t_list *tmp;
	char **str;
	t_var *content;

	tmp = *datas->export;
	str = ft_split(line, '=');
	while (ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	free(((t_var *)tmp->content)->value);
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	content = fill_tmp(line);
	tmp = ft_lstnew(content);
	ft_lstadd_back(datas->env, tmp);
	free_double(str);
}

void	actualize_export_actualize_env(char *line, t_big *datas)
{
	t_list *tmp;
	char **str;

	tmp = *datas->env;
	str = ft_split(line, '=');
	while (ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	free(((t_var *)tmp->content)->value); //PEUT CAUSER DES LEAKS
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	tmp = *datas->export;
	while (ft_strcmp(str[0], ((t_var *)tmp->content)->var))
		tmp = tmp->next;
	free(((t_var *)tmp->content)->value); //PEUT CAUSER DES LEAKS
	((t_var *)tmp->content)->value = ft_strdup(str[1]);
	free_double(str);
}

void	add_hidden_add_export_add_env(char *line, t_big *datas)
{
	add_to_list(line, datas->env);
	add_to_list(line, datas->export);
	add_to_list(line, datas->hidden);
}

void	add_hidden_add_export(char *line, t_big *datas)
{
	t_var	*content;
	t_list	*new;

	content = (t_var *)malloc(sizeof(t_var));
	content->var = ft_strdup(line);
	content->value = 0;
	new = ft_lstnew(content);
	ft_lstadd_back(datas->export, new);
	content = (t_var *)malloc(sizeof(t_var));
	content->var = ft_strdup(line);
	content->value = 0;
	new = ft_lstnew(content);
	ft_lstadd_back(datas->hidden, new);
}

int		ft_export(char **arg, t_big *datas)
{
	t_list	*tmp;
	int		i;
	//int		pos;

	i = 1;
	if (!arg[i])
	{
		tmp = *(datas->export);
		while (tmp)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(((t_var *)tmp->content)->var, STDOUT_FILENO);
			if (((t_var *)tmp->content)->value)
			{
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putchar_fd('\"', STDOUT_FILENO);
				ft_putstr_fd(((t_var *)tmp->content)->value, STDOUT_FILENO);
				ft_putchar_fd('\"', STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
			tmp = tmp->next;
		}
	}
	else
	{
		while (arg[i])
		{
			if (!check_arg_conformity(arg[i]))
			{
				ft_putstr_fd("minishellrose: export: `", STDOUT_FILENO);
				ft_putstr_fd(arg[i], STDOUT_FILENO);
				ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
			} 
			else if (!ft_strchr(arg[i], '=')) 																				//PAS DE '='; nas
			{
				if (check_duplicate(*datas->hidden, arg[i]) && !check_duplicate(*datas->export, arg[i])) 				//SI PRESENT DANS HIDDEN ALORS ENV ET EXPORT HERITENT DE HIDDEN
					add_hidden_to_env_export(arg[i], datas);
				else if (!check_duplicate(*datas->hidden, arg[i]) && !check_duplicate(*datas->export, arg[i])) 			//SI ABSENT DE HIDDEN ET DE EXPORT ALORS EXPORT ET HIDDEN S'ACTUALISENT
					add_hidden_add_export(arg[i], datas);
			}
			else if (ft_strchr(arg[i], '=') && !is_plus_left(arg[i])) 																			//AVEC '='; nas=gentille
			{
				if (!check_duplicate(*datas->hidden, arg[i])) 															//VARIABLE N'EXISTE PAS ENCORE, LA CREER DANS LES 3 LISTES 
					add_hidden_add_export_add_env(arg[i], datas);
				else 																									//VARIABLE EXISTE DANS ENV
				{
					actualize_list(arg[i], *datas->hidden);																//ACTUALIZE LIST HIDDEN
					if (check_duplicate(*datas->export, arg[i]) && !check_duplicate(*datas->env, arg[i])) 				//VARIABLE ACTUALISEE
						actualize_export_add_env(arg[i], datas);
					else if (check_duplicate(*datas->export, arg[i]) && check_duplicate(*datas->env, arg[i]))
						actualize_export_actualize_env(arg[i], datas);
					else if (!check_duplicate(*datas->export, arg[i])) 													//VARIABLE ACTUALISEE ET IMPORTEE DANS EXPORT
						add_hidden_to_env_export(arg[i], datas);
				}
			}
			else if (ft_strchr(arg[i], '=') && is_plus_left(arg[i]))
			{
				if (!check_plus_conformity(arg[i]))
				{
					ft_putstr_fd("minishellrose: export: `", STDOUT_FILENO);
					ft_putstr_fd(arg[i], STDOUT_FILENO);
					ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
				}
				else
				{
					
				}
			}
			i++;
		}
	}
	*datas->export = ft_lst_sort(*datas->export, &cmp_list);
	return (0);
}
