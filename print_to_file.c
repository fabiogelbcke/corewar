/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/02/10 18:00:07 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ 

#include "asm.h"

char			*get_file_name(char *filename)
{
	char		*out_name;
	char		**tmp;

	tmp = ft_strsplit(filename, '.');
	if (ft_strarr_len(tmp) > 1)
	{
		tmp[ft_strarr_len(tmp) - 1] = NULL;
	}

	out_name = ft_join_strarr(tmp, '.');
	ft_free_strarr(tmp);
	out_name = ft_strappend_free(out_name, ft_strdup(".cor"));
	return (out_name);
}

char			hex_to_char(char *hex)
{
	char		c;

	c = 0;
	c += (hex[3] > '9') ? hex[3] - 87 : hex[3] - 48;
	c += (hex[2] > '9') ? 16 * (hex[2] - 87) : 16 * (hex[2] - 48);
	return (c);
}

void			write_output(char **output, int fd)
{
	int			i;
	int			j;
	char		**comma_split;

	i = 0;
	while (output[i])
	{
		j = 0;
		comma_split = ft_strsplit(output[i], ',');
		while (comma_split[j])
		{
			ft_putchar_fd(hex_to_char(comma_split[j]), fd);
			j++;
		}
		ft_free_strarr(comma_split);
		i++;
	}
}

void			print_to_file(char **output, char *filename)
{
	char		*out_name;
	int			fd;

	out_name = get_file_name(filename);
	fd = open(out_name, O_WRONLY|O_CREAT);
	free(out_name);
	if (fd == -1)
	{
		ft_free_strarr(output);
		ft_putendl("Couldn't create output file");
		exit(1);
	}
	write_output(output, fd);
	close(fd);
}
