/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 15:13:58 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/12 16:04:40 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_compare(void *i, void *j)
{
	if (*(int *)i > *(int *)j)
		return (1);
	else
		return (0);
}

t_list	*ft_sort_list(t_list *lst, int (*f)())
{
	t_list *start;
	void *hold;

	start = lst;
	while (lst->next)
	{
		if ((*f)(lst->content, lst->next->content))
		{
			hold = lst->content;
			lst->content = lst->next->content;
			lst->next->content = hold;
			lst = start;
		}
		else
			lst = lst->next;
	}
	lst = start;
	return (lst);
}

int 	main(void)
{
	t_list *tmp;
	t_list **start;
	int *i;
	int *j;
	int *k;
	int *l;
	int *m;

	i = (int *)malloc(sizeof(int));
	j = (int *)malloc(sizeof(int));
	k = (int *)malloc(sizeof(int));
	l = (int *)malloc(sizeof(int));
	m = (int *)malloc(sizeof(int));
	*i = 10;
	*j = 10003;
	*k = 56;
	*l = 42;
	*m = -3;
	start = (t_list **)malloc(sizeof(t_list));
	*start = ft_lstnew((i));
	tmp = ft_lstnew(j);
	ft_lstadd_back(start, tmp);
	tmp = ft_lstnew(k);
	ft_lstadd_back(start, tmp);
	tmp = ft_lstnew(l);
	ft_lstadd_back(start, tmp);
	tmp = ft_lstnew(m);
	ft_lstadd_back(start, tmp);
	tmp = *start;
	while (tmp)
	{
		printf("%i\n", *(int *)tmp->content);
		tmp = tmp->next;
	}
	*start = ft_sort_list(*start, ft_compare);
	tmp = *start;
	while (tmp)
	{
		printf("%i\n", *(int *)tmp->content);
		tmp = tmp->next;
	}

	return (0);
}
