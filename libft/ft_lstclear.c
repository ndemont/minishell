/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 18:10:43 by gpetit            #+#    #+#             */
/*   Updated: 2020/12/27 13:44:37 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*l;

	l = *lst;
	while (l->next)
	{
		temp = l;
		l = l->next;
		ft_lstdelone(temp, del);
	}
	if (l)
		ft_lstdelone(l, del);
	*lst = NULL;
}
