/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhuber <nhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:36:17 by nhuber            #+#    #+#             */
/*   Updated: 2017/03/03 14:43:41 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		free_routines(t_routine *routines)
{
	t_routine	*next;

	while (routines)
	{
		next = routines->next;
		free(routines->name);
		free(routines);
		routines = next;
	}
}

int			is_routine(char *line)
{
	int		is_rout;
	int		i;

	is_rout = !is_empty(line) && !is_comment(line);
	is_rout = is_rout && !is_name(line);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	while (line[i] && (line[i] != ' ' && line[i] != '\t'))
		i++;
	is_rout = is_rout && (i > 0 && line[i - 1] == LABEL_CHAR);
	return (is_rout);
}

static int	routine_exists(char *name, t_routine *routines)
{
	while (routines)
	{
		if (!ft_strcmp(name, routines->name))
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
	i = -1;
	if (ft_strarr_len(split_line) == 0)
		return (0);
	while (++i < (int)ft_strlen(split_line[0]))
	{
		j = -1;
		while (LABEL_CHARS[++j])
		{
			if (LABEL_CHARS[j] == split_line[0][i])
				break ;
		}
		if (!LABEL_CHARS[j])
			return (0);
	}
	i = (routine_exists(split_line[0], routines)) ? 0 : 1;
	ft_free_strarr(split_line);
	return (i);
}
