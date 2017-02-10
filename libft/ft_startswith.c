/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_startswith.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/01/23 19:22:08 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_startswith(char *str, char *sub)
{
	if (!str || !sub)
		return (0);
	while (*str && *sub)
	{
		if (*str != *sub)
			return (0);
		str++;
		sub++;
	}
	return !(*sub);
}
