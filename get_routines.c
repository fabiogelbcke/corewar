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

int			get_bytecodes_count(char **split_line)
{
	int		count;
	int		sl_len;
	int		i;
	char	**params;

	sl_len = ft_strarr_len(split_line);
	if (sl_len == 0)
		return (0);
	count = 2;
	params = ft_strsplit(split_line[sl_len - 1], SEPARATOR_CHAR);
	sl_len = ft_strarr_len(params);
	if (sl_len == 0)
		return (count);
	i = 0;
	while (params[i])
	{
		count += get_param_size(params[i], split_line[0]);
		i++;
	}
	return (count);
}

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
