/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:20:11 by gpetit            #+#    #+#             */
/*   Updated: 2021/03/26 11:21:15 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_pwd(char *str) //integrer dans structure
{
	char *buf;
	int fd;

	void *str; //we ignore the input
	buf = NULL; //set BUF a null pour que getcwd remalloc la bonne taille (MAN)
	buf = getcwd(buf, 0); //Should I control errno ??
	if (!buf)
		return (-1); //set structure error flag at -1
}

