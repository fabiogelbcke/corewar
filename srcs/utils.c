/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/02 14:16:59 by fschuber         ###   ########.fr       */
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
	count = 1;
	if (has_acb(split_line[0]))
		count += 1;
	params = get_params(split_line);
	sl_len = ft_strarr_len(params);
	if (sl_len == 0)
		return (count);
	i = 0;
	while (params[i])
	{
		count += get_param_size(params[i], split_line[0]);
		i++;
	}
	ft_free_strarr(params);
	return (count);
}

char		*int_to_bytecode(long int val, int bytes)
{
	char	*bytecode;
	int		size;
	int		i;

	if (val < 0)
		return (int_to_bytecode(ft_pow(2, 8 * bytes) + val, bytes));
	size = 5 * bytes;
	bytecode = malloc(sizeof(char) * size);
	i = size - 1;
	while (--i >= 0)
	{
		if ((i + 4) % 5 == 0)
			bytecode[i] = 'x';
		else if ((i % 5) == 0)
			bytecode[i] = '0';
		else if (((i + 1) % 5) == 0)
			bytecode[i] = ',';
		else
		{
			bytecode[i] = ((val % 16) > 9) ? (val % 16) + 87 : (val % 16) + 48;
			val = val / 16;
		}
	}
	bytecode[size - 1] = 0;
	return (bytecode);
}

int			has_acb(char *cmd)
{
	if (ft_strcmp(cmd, "fork") && ft_strcmp(cmd, "zjmp")
		&& ft_strcmp(cmd, "live"))
		return (1);
	return (0);
}

char		**get_params(char **split_input)
{
	int		i;
	char	*tmp;
	char	**params;

	tmp = ft_join_strarr(&(split_input[1]), ' ');
	params = ft_strsplit(tmp, SEPARATOR_CHAR);
	free(tmp);
	i = 0;
	while (params[i])
	{
		tmp = ft_strtrim(params[i]);
		free(params[i]);
		params[i] = tmp;
		i++;
	}
	i = 0;
	return (params);
}
