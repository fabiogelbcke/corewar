/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhuber <nhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 09:02:16 by nhuber            #+#    #+#             */
/*   Updated: 2017/03/03 11:10:09 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_file_name(char *filename)
{
	char	*out_name;
	int		i;

	out_name = ft_strdup(filename);
	i = ft_strlen(out_name) - 1;
	while (i > 0 && out_name[i] != '.')
		i--;
	if (i != 0)
		out_name[i] = 0;
	out_name = ft_strappend_free(out_name, ft_strdup(".cor"));
	return (out_name);
}

int		valid_name(char *line)
{
	int		i;
	char	*tmp;

	if (!line)
		return (0);
	line = ft_strtrim(line);
	if (!ft_startswith(line, NAME_CMD_STRING))
	{
		free(line);
		return (0);
	}
	i = ft_strlen(NAME_CMD_STRING);
	tmp = ft_strtrim(&(line[i]));
	free(line);
	if (ft_strlen(tmp) < 2 || tmp[0] != '"' || tmp[ft_strlen(tmp) - 1] != '"'
			|| ft_strlen(tmp) > 2 + PROG_NAME_LENGTH)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}
