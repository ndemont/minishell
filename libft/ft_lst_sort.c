/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:20:12 by gpetit            #+#    #+#             */
/*   Updated: 2021/04/12 16:20:29 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_sort(t_list *lst, int (*f)())
{
	t_list	*start;
	void	*hold;

	if (!lst)
		return (NULL);
	start = lst;
	while (lst->next)
	{
		if ((*f)(lst->content, lst->next->content) > 0)
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
