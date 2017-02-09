/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/01/23 19:22:08 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc(void *ptr, size_t size, size_t prev_size)
{
	char	*new_ptr;
	int		copy_size;
	
	if (!ptr)
		return malloc(size);
	if (size == 0)
		return NULL;
	new_ptr = malloc(size);
	if (!new_ptr)
		return NULL;
	copy_size = (prev_size > size) ? size : prev_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return new_ptr;
}
