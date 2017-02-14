/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_routines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:48 by fschuber          #+#    #+#             */
/*   Updated: 2017/01/23 18:48:50 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"



t_routine	*create_routine(char *name, int pos)
{
	t_routine *new_rout;

	new_rout = malloc(sizeof(t_routine));
	new_rout->name = ft_strdup(name);
	new_rout->pos = pos;
	return (new_rout);
}

t_routine	*get_routines(char **input)
{
	int		i;
	t_routine *last;
	t_routine *curr;
	int		pos;
	char	**split_line;

	i = 0;
	last = NULL;
	pos = 0;
	while (input[i])
	{
		if (is_routine(input[i]))
		{
			split_line = ft_split_spaces(input[i]);
			curr = create_routine(split_line[0], pos);
			curr->next = last;
			last = curr;
			input[i] = ft_join_strarr(&split_line[1], ' ');
		}
		pos += get_bytecodes_count(ft_split_spaces(input[i]));
		i++;
	}
	return curr;
}
