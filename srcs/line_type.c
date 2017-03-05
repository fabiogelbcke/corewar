/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:11:06 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/05 20:55:39 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			is_empty(char *line)
{
	int		i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (1);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i])
		return (0);
	return (1);
}

int			is_comment(char *line)
{
	int		i;

	i = 0;
	if (is_empty(line))
		return (0);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] && (line[i] == '#' || line[i] == ';'))
		return (1);
	return (0);
}

int			is_name(char *line)
{
	int		i;

	i = 0;
	if (is_empty(line))
		return (0);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!ft_startswith(&line[i], NAME_CMD_STRING))
		return (0);
	return (1);
}

int			is_initial_comment(char *line)
{
	int		i;

	i = 0;
	if (is_empty(line))
		return (0);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!ft_startswith(&line[i], COMMENT_CMD_STRING))
		return (0);
	return (1);
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
