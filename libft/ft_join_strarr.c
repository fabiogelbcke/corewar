/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 09:10:07 by fschuber          #+#    #+#             */
/*   Updated: 2014/11/28 19:47:54 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_join_strarr(char **strarr, char separator)
{
	int		i;
	int		j;
	char	*joined;
	size_t	size;

	i = 0;
	size = 0;
	while (strarr[i])
	{
		j = 0;
		while (strarr[i][j])
			j++;
		size += j + 1;
		i++;
	}
	joined = ft_memalloc(sizeof(char) * size + 1);
	size = 0;
	i = 0;
	while (strarr[i])
	{
		j = 0;
		while (strarr[i][j])
			joined[size++] = strarr[i][j++];
		if (strarr[i + 1] && ft_strlen(strarr[i + 1]) > 0)
			joined[size++] = separator;
		i++;
	}
	joined[size] = '\0';
	return (joined);
}
