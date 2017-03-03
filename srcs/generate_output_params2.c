/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_output_params2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhuber <nhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 11:55:54 by nhuber            #+#    #+#             */
/*   Updated: 2017/03/03 17:33:05 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_label_param(char *param, int line_pos, int size,
		t_routine *routine)
{
	char	**split_param;
	int		i;

	if (!routine || !ft_strrchr(param, LABEL_CHAR))
		return (NULL);
	split_param = ft_strsplit(param, LABEL_CHAR);
	if (!split_param)
		return (NULL);
	i = ft_strarr_len(split_param) - 1;
	while (ft_strcmp(routine->name, split_param[i]))
	{
		if (!routine->next)
		{
			ft_putstr(split_param[i]);
			ft_putendl(" : label doesn't exist");
			ft_free_strarr(split_param);
			exit(1);
		}
		routine = routine->next;
	}
	ft_free_strarr(split_param);
	return (int_to_bytecode(routine->pos - line_pos, size));
}
