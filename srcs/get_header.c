/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/05 20:50:33 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char				*get_name_comment(char *line, int type)
{
	char			*nc;
	char			*tmp;
	char			*tmp2;
	int				i;

	if (type == 1)
		i = ft_strlen(NAME_CMD_STRING);
	else
		i = ft_strlen(COMMENT_CMD_STRING);
	tmp2 = ft_strtrim(line);
	tmp = ft_strtrim(&(tmp2[i]));
	free(tmp2);
	tmp[ft_strlen(tmp) - 1] = 0;
	nc = malloc(sizeof(char) * ft_strlen(tmp));
	tmp2 = ft_strrchr(tmp, '"');
	if (tmp2)
		nc = ft_strcpy(nc, tmp2 + 1);
	else
	{
		free(nc);
		return (NULL);
	}
	free(tmp);
	return (nc);
}

int					get_magic(char *magic_hex)
{
	int				i;
	unsigned int	magic;
	int				mult;

	i = ft_strlen(magic_hex) - 1;
	magic = 0;
	mult = 1;
	while (i > 1)
	{
		if (magic_hex[i] >= 48 && magic_hex[i] <= 57)
			magic += (magic_hex[i] - 48) * mult;
		else
			magic += (magic_hex[i] - 97) * mult;
		mult = mult * 16;
		i--;
	}
	return (mult);
}

static void			get_header_nc(t_header *header, char **input,
		int *i, int *done)
{
	char			*tmp;

	if (is_name(input[*i]) && (*done & 1) == 0 && valid_name(input[*i]))
	{
		tmp = get_name_comment(input[*i], 1);
		ft_strcpy((*header).prog_name, tmp);
		free(tmp);
		*done += 1;
	}
	else if (is_initial_comment(input[*i]) && ((*done & 2) == 0)
			&& valid_initial_comment(input, *i))
	{
		*i += add_full_comment(header, input, *i) - 1;
		*done += 2;
	}
}

t_header			get_header(char **input, int *prog_start)
{
	t_header		header;
	int				i;
	int				done;

	i = 0;
	done = 0;
	header.magic = COREWAR_EXEC_MAGIC;
	while (input[i])
	{
		if (done == 3)
		{
			*prog_start = i;
			return (header);
		}
		else if (!is_name(input[i]) && !is_initial_comment(input[i]) &&
				!is_empty(input[i]) && !is_comment(input[i]))
			break ;
		else
			get_header_nc(&header, input, &i, &done);
		i++;
	}
	*prog_start = 0;
	return (header);
}
