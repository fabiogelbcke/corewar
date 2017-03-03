/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhuber <nhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:44:07 by nhuber            #+#    #+#             */
/*   Updated: 2017/03/03 15:48:08 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			eliminate_comments(char *line)
{
	char		*ptr;

	if (ft_strrchr(line, COMMENT_CHAR))
	{
		ptr = ft_strrchr(line, COMMENT_CHAR);
		*ptr = '\0';
	}
	if (ft_strrchr(line, ';'))
	{
		ptr = ft_strrchr(line, ';');
		*ptr = '\0';
	}
}
