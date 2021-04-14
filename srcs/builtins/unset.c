/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:00:09 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/14 18:05:00 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        ft_delete_elem(t_list *elem)
{
    if (elem)
    {
        if (elem->content)
        {
            if (((t_var *)elem->content)->var)
            {
                free(((t_var *)elem->content)->var);
                ((t_var *)elem->content)->var = 0;
            }
            if (((t_var *)elem->content)->value)
            {
                free(((t_var *)elem->content)->value);
                ((t_var *)elem->content)->value = 0;
            }
            free(elem->content);
            elem->content = 0;
        }
        free(elem);
        elem = 0;
    }
}

int      ft_lst_remove(t_list **list, char *var)
{
    t_list  *elem;
    t_list  *prev;

    elem = *list;
    prev = 0;
    while (elem)
    {
        if (!ft_strcmp(((t_var *)elem->content)->var, var))
        {
            ft_delete_elem(elem);
            if (!prev)
                list = &elem->next;
            else
                prev->next = elem->next;
        }
        else
            prev = elem;
        elem = elem->next;
    }
    return (1);
}

int			ft_unset(char **arg, t_big *datas)
{
    int i;

    i = 1;
    write(1, "begin\n", 6);
    while (arg[i])
    {
        write(1, "env\n", 4);
        ft_lst_remove(datas->env, arg[i]);
        write(1, "export\n", 7);
        ft_lst_remove(datas->export, arg[i]);
        //ft_lst_remove(datas->hidden, arg[i]);
        i++;
    }
    write(1, "end\n", 4);
    return (1);
}