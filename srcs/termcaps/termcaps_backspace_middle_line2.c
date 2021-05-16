/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_backspace_middle_line2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 19:08:05 by gpetit            #+#    #+#             */
/*   Updated: 2021/05/16 19:08:13 by gpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_the_mess(char **tmp, char **oldline, char **line)
{
	clean_free(tmp);
	clean_free(oldline);
	clean_free(line);
}
