/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/03 11:08:28 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			valid_initial_comment(char *line)
{
	int		i;
	char	*tmp;

	if (!line)
		return (0);
	line = ft_strtrim(line);
	if (!ft_startswith(line, COMMENT_CMD_STRING))
	{
		free(line);
		return (0);
	}
	i = ft_strlen(COMMENT_CMD_STRING);
	tmp = ft_strtrim(&(line[i]));
	free(line);
	if (ft_strlen(tmp) < 2 || tmp[0] != '"' || tmp[ft_strlen(tmp) - 1] != '"'
		|| ft_strlen(tmp) > 2 + COMMENT_LENGTH)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

t_op		*valid_instruction_name(char *name)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(name, g_op_tab[i].name))
			return (&g_op_tab[i]);
		i++;
	}
	return (NULL);
}

int			arg_number(char *param)
{
	if (valid_registry(param))
		return (T_REG);
	else if (valid_dir_arg(param))
		return (T_DIR);
	else if (valid_ind_arg(param))
		return (T_IND);
	return (0);
}

int			valid_parameters(char **params, t_op instruction)
{
	int		i;

	i = 0;
	while (params[i] && instruction.args_type[i])
	{
		if (i == MAX_ARGS_NUMBER)
			return (0);
		if ((arg_number(params[i]) & instruction.args_type[i]) == 0)
			return (0);
		i++;
	}
	if (i != (int)ft_strlen(instruction.args_type) || params[i] != NULL)
		return (0);
	return (1);
}

int			valid_instruction(char *line)
{
	char	**split_line;
	char	**params;
	t_op	*instruction;

	if (!is_instruction(line))
		return (0);
	split_line = ft_split_spaces(line);
	if (split_line == NULL)
		return (0);
	instruction = valid_instruction_name(split_line[0]);
	if (instruction == NULL)
	{
		ft_free_strarr(split_line);
		return (0);
	}
	params = get_params(split_line);
	if (!valid_parameters(params, *instruction))
	{
		ft_free_strarr(params);
		ft_free_strarr(split_line);
		return (0);
	}
	ft_free_strarr(split_line);
	ft_free_strarr(params);
	return (1);
}
