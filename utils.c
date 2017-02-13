/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/02/10 18:00:07 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ 

#include "asm.h"

int			get_dir_size(char *cmd)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(op_tab[i].name, cmd))
			return (op_tab[i].dir_size == 0 ? 4 : 2);
		i++;
	}
	return 0;
}

int			get_param_size(char *param, char *cmd)
{
	if (param[0] == 'r')
		return 1;
	else if (param[0] == DIRECT_CHAR)
		return get_dir_size(cmd);
	else
		return 2;
}

int			int_to_bytecode(int val, int bytes)
{
	char	*bytecode;
	int		size;

	size = 4 * bytes  - 1;
	bytecode = malloc(sizeof(char) * size);
}
