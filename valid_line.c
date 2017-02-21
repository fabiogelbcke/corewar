/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/02/10 18:00:07 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			valid_initial_comment(char *line)
{
	char	**split_line;

	if (!is_initial_comment(line))
		return (0);
	split_line = ft_split_spaces(line);
	if (ft_strarr_len(split_line) != 2)
		return (0);
	if (ft_strlen(split_line[1]) > COMMENT_LENGTH + 2)
		return (0);
	if (split_line[1][0] != '"' || split_line[1][ft_strlen(split_line[1] - 1)])
		return (0);
	return (1);
}

int			valid_name(char *line)
{
	char	**split_line;

	if (!is_name(line))
		return (0);
	split_line = ft_split_spaces(line);
	if (ft_strarr_len(split_line) != 2)
		return (0);
	if (ft_strlen(split_line[1]) > PROG_NAME_LENGTH + 2)
		return (0);
	if (split_line[1][0] != '"' || split_line[1][ft_strlen(split_line[1] - 1)])
		return (0);
	return (1);
}

int			routine_exists(char *name, t_routine *routines)
{
	while (routines)
	{
		if (!ft_strcmp(name,routines->name))
			return (1);
		routines = routines->next;
	}
	return (0);
}

int			valid_routine(char *line, t_routine *routines)
{
	char	**split_line;
	int		i;
	int		j;

	split_line = ft_split_spaces(line);
	i = 0;
	if (ft_strarr_len(split_line) == 0)
		return (0);
	while (i < ft_strlen(split_line[0]))
	{
		j = 0;
		while (LABEL_CHARS[j])
		{
			if (LABEL_CHARS[j] == split_line[0][i])
			{
				i++;
				break;
			}
			j++;
		}
		if (!LABEL_CHARS[j])
			return (0);
	}
	if (routine_exists(split_line[0], routines))
		return (0);
	return (1);
}

t_op		*valid_instruction_name(char *name)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(name, op_tab[i].name))
			return (&op_tab[i]);
		i++;
	}
	return (NULL);
}

int			arg_number(char *param)
{
	if (param[0] == 'r' && valid_registry(param))
		return (T_REG);
	else if (param[0] == DIRECT_CHAR && valid_dir_arg(param))
	{
		return (T_DIR);
	}
	else if ((ft_isnbr(param)
			  || param[0] == LABEL_CHAR) && valid_ind_arg(param))
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
		{
			ft_putendl(params[i]);
			return (0);
		}
		if ((arg_number(params[i]) & instruction.args_type[i]) == 0)
		{
			ft_putendl(params[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int			valid_instruction(char *line)
{
	char	**split_line;
	int		i;
	char	**params;
	t_op	*instruction;
	
	if (!is_instruction(line))
		return (0);
	split_line = ft_split_spaces(line);
	instruction = valid_instruction_name(split_line[0]);
	if (instruction == NULL)
		return (0);
	params = get_params(split_line);
	if (!valid_parameters(params, *instruction))
		return (0);
	ft_free_strarr(split_line);
	ft_free_strarr(params);
	return (1);
}
