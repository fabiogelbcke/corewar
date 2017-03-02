/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:11:06 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/02 14:12:00 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			is_empty(char *line)
{
	char	**split_line;

	if (ft_strlen(line) == 0)
		return (1);
	split_line = ft_split_spaces(line);
	if (ft_strarr_len(split_line) == 0)
	{
		ft_free_strarr(split_line);
		return (1);
	}
	ft_free_strarr(split_line);
	return (0);
}

int			is_comment(char *line)
{
	char	**split_line;

	if (is_empty(line))
		return (0);
	split_line = ft_split_spaces(line);
	if (split_line[0][0] != COMMENT_CHAR)
	{
		ft_free_strarr(split_line);
		return (0);
	}
	ft_free_strarr(split_line);
	return (1);
}

int			is_name(char *line)
{
	char	**split_line;

	if (is_empty(line))
		return (0);
	split_line = ft_split_spaces(line);
	if (ft_strcmp(split_line[0], NAME_CMD_STRING))
	{
		ft_free_strarr(split_line);
		return (0);
	}
	ft_free_strarr(split_line);
	return (1);
}

int			is_initial_comment(char *line)
{
	return (!is_empty(line) && ft_startswith(line, COMMENT_CMD_STRING));
}

int			is_routine(char *line)
{
	int		is_rout;
	char	**split_line;
	char	*first_word;

	is_rout = !is_empty(line) && !is_comment(line);
	is_rout = is_rout && !is_name(line);
	is_rout = is_rout && !is_initial_comment(line);
	split_line = ft_split_spaces(line);
	first_word = split_line[0];
	is_rout = is_rout && first_word[ft_strlen(first_word) - 1] == LABEL_CHAR;
	ft_free_strarr(split_line);
	return (is_rout);
}

int			is_instruction(char *line)
{
	int		is_inst;

	is_inst = !is_empty(line) && !is_comment(line);
	is_inst = is_inst && !is_name(line);
	is_inst = is_inst && !is_initial_comment(line);
	is_inst = is_inst && !is_routine(line);
	return (is_inst);
}
