/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/02 13:49:13 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char				*get_name_comment(char *line, int type)
{
	char			*nc;
	char			*tmp;
	int				i;

	if (type == 1)
		i = ft_strlen(NAME_CMD_STRING);
	else
		i = ft_strlen(COMMENT_CMD_STRING);
	tmp = ft_strtrim(&(line[i]));
	tmp[ft_strlen(tmp) - 1] = 0;
	nc = malloc(sizeof(char) * ft_strlen(tmp));
	nc = ft_strcpy(nc, &(tmp[1]));
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
	//TODO control for magic that might be bigger than unsigned int upper limit
	return (mult);
}

header_t			get_header(char **input, int *prog_start)
{
	header_t		header;
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
		else if (is_name(input[i]) && (done & 1) == 0 && valid_name(input[i]))
		{
			ft_strcpy(header.prog_name, get_name_comment(input[i], 1));
			done += 1;
		}
		else if (is_initial_comment(input[i]) && ((done & 2) == 0)
				 && valid_initial_comment(input[i]))
		{
			ft_strcpy(header.comment, get_name_comment(input[i], 2));
			done += 2;
		}
		else if (!is_empty(input[i]) && !is_comment(input[i]))
			break ;
		i++;
	}
	*prog_start = 0;
	return (header);
}
