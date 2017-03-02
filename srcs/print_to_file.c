/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/02 14:08:28 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ 

#include "asm.h"

char			*get_file_name(char *filename)
{
	char		*out_name;
	int			i;

	out_name = ft_strdup(filename);
	i = ft_strlen(out_name) - 1;
	while (i > 0 && out_name[i] != '.')
		i--;
	if (i != 0)
		out_name[i] = 0;
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

void			write_program(char **output, int fd)
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

void			print_header_int(int val, int fd)
{
	char		*str;
	char		**split;
	int			i;
	
	str = int_to_bytecode(val, sizeof(unsigned int));
	split = ft_strsplit(str, ',');
	free(str);
	i = 0;
	while (split[i])
		ft_putchar_fd(hex_to_char(split[i++]), fd);
	ft_free_strarr(split);
}

void			write_header(header_t header, int fd)
{
	int			i;
	
	print_header_int(header.magic, fd);
	i = 0;
	while (header.prog_name[i])
		ft_putchar_fd(header.prog_name[i++], fd);
	while (i < PROG_NAME_LENGTH + 4)
	{
		i++;
		ft_putchar_fd(0, fd);
	}
	print_header_int(header.prog_size, fd);
	i = 0;
	while (header.comment[i])
		ft_putchar_fd(header.comment[i++], fd);
	while (i < COMMENT_LENGTH + 4)
	{
		i++;
		ft_putchar_fd(0, fd);
	}
}

void			print_to_file(char **output, char *filename, header_t header)
{
	char		*out_name;
	int			fd;

	out_name = get_file_name(filename);
	fd = open(out_name, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd == -1)
	{
		ft_free_strarr(output);
		perror(out_name);
		free(out_name);
		exit(1);
	}

	write_header(header, fd);
	write_program(output, fd);
	ft_putstr("Printing to file ");
	ft_putendl(out_name);
	free(out_name);
	close(fd);
}
