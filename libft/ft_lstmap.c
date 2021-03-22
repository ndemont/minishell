/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 19:49:42 by gpetit            #+#    #+#             */
/*   Updated: 2020/12/27 13:46:37 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*start;

	(void)del;
	if (!lst)
		return (NULL);
	new = malloc(sizeof(t_list) * 1);
	if (!(new))
		return (NULL);
	start = new;
	while (lst)
	{
		new->content = f(lst->content);
		lst = lst->next;
		if (lst)
		{
			new->next = malloc(sizeof(t_list) * 1);
			if (!(new))
				return (NULL);
			new = new->next;
		}
		else
			new->next = NULL;
	}
	return (start);
}
