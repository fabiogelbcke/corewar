/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_output_params.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/06 13:13:30 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*get_registry_bytecode(char *param)
{
	int		val;

	val = ft_atoi(&param[1]);
	return (int_to_bytecode(val, 1));
}

char		*get_dir_bytecode(char *param, char *cmd,
								int line_pos, t_routine *routines)
{
	int		val;

	if (param[1] == ':')
	{
		return (get_label_param(param, line_pos,
					get_param_size(param, cmd), routines));
	}
	else
	{
		val = atoi(&param[1]);
		return (int_to_bytecode(val, get_param_size(param, cmd)));
	}
}

char		*get_ind_bytecode(char *param, char *cmd,
								int line_pos, t_routine *routines)
{
	int		val;

	if (param[0] == ':')
	{
		return (get_label_param(param, line_pos,
								get_param_size(param, cmd), routines));
	}
	else
	{
		val = ft_atoi(param);
		return (int_to_bytecode(val, get_param_size(param, cmd)));
	}
}

char		*get_param_bc(char *param, char *cmd,
							int line_pos, t_routine *routines)
{
	if (param[0] == 'r')
		return (get_registry_bytecode(param));
	else if (param[0] == DIRECT_CHAR)
		return (get_dir_bytecode(param, cmd, line_pos, routines));
	else
		return (get_ind_bytecode(param, cmd, line_pos, routines));
}

char		*get_parameters_bytecode(char **params, char *cmd,
										int line_pos, t_routine *routines)
{
	char		*params_bytecode;
	int			i;
	char		*separator;
	char		*old;
	char		*tmp;

	separator = ft_strdup(" ");
	separator[0] = SEPARATOR_CHAR;
	params_bytecode = ft_strdup("");
	i = -1;
	while (params[++i])
	{
		old = params_bytecode;
		tmp = get_param_bc(params[i], cmd, line_pos, routines);
		params_bytecode = ft_strjoin(params_bytecode, tmp);
		free(tmp);
		free(old);
		old = params_bytecode;
		params_bytecode = ft_strjoin(params_bytecode, separator);
		free(old);
	}
	free(separator);
	if (i > 0)
		params_bytecode[ft_strlen(params_bytecode) - 1] = '\0';
	return (params_bytecode);
}
