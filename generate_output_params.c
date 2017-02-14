/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_output_params.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/02/10 18:00:07 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ 

#include "asm.h"

char		*get_registry_bytecode(char *param)
{
	int		val;

	val = ft_atoi(&param[1]);
	return int_to_bytecode(val, 1);
}

char		*get_dir_bytecode(char *param, char *cmd, int line_pos)
{
	int		val;

	if (param[1] == ':')
	{
		return ft_strdup("oi");
	}
	else
	{
		val = ft_atoi(&param[1]);
		return int_to_bytecode(val, get_param_size(param, cmd));
	}
}

char		*get_ind_bytecode(char *param, char *cmd, int line_pos)
{
	int		val;

	if (param[0] == ':')
	{
		return ft_strdup("oi");
	}
	else
	{
		val = ft_atoi(param);
		return int_to_bytecode(val, get_param_size(param, cmd));
	}
}

char		*get_param_bc(char *param, char *cmd, int line_pos)
{
	if (param[0] == 'r')
		return get_registry_bytecode(param);
	else if (param[0] == DIRECT_CHAR)
		return get_dir_bytecode(param, cmd, line_pos);
	else
		return get_ind_bytecode(param, cmd, line_pos);
}

char		*get_parameters_bytecode(char **params, char *cmd, int line_pos)
{
	char		*params_bytecode;
	int			i;
	char		*separator;

	separator = ft_strdup("\0\0");
	separator[0] = SEPARATOR_CHAR;
	params_bytecode = ft_strdup("");
	i = 0;
	while (params[i])
	{
		params_bytecode = ft_strjoin(params_bytecode, get_param_bc(params[i], cmd, line_pos));
		params_bytecode = ft_strjoin(params_bytecode, separator);
		i++;
	}
	if (i > 0)
		params_bytecode[ft_strlen(params_bytecode) - 1] = '\0';
	return params_bytecode;
}
