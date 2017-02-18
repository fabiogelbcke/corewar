/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/02/18 17:11:04 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ 

#include "asm.h"

char			**get_input(char *filename)
{
	char		**input;
	int			total_size;
	int			i;
	int			fd;
	
	input = ft_memalloc(BUF_SIZE * sizeof(char*));
	if (!input)
		return (NULL);
	total_size = BUF_SIZE;
	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{		
		free(input);
		return (NULL);
	}
	while (++i)
	{
		if (ft_gnl(fd, &(input[i - 1])) == 0)
			break;
		if (i == total_size - 1)
		{
			input = realloc(input, (total_size + BUF_SIZE) * sizeof(char*));
			if (input == NULL)
				return (NULL);
			total_size += BUF_SIZE;
		}
	}
	input[i] = NULL;
	close(fd);
	return (input);
}

int				main(int argc, char **argv)
{
	char		**input;
	char		**output;
	header_t	header;
	int			prog_start;

	if (argc < 2)
		return -1;
	input = get_input(argv[1]);
	if (!input)
	{
		perror(NULL);
		exit(1);
	}
	header = get_header(input, &prog_start);
	ft_putendl(header.prog_name);
	ft_putendl(header.comment);
	ft_putnbr(header.magic);
	ft_putendl("");
	if (prog_start == 0)
	{
		ft_putendl("Invalid header");
		free(input);
		exit(1);
	}
	output = generate_output(input, ft_strarr_len(input));
	ft_free_strarr(input);
	print_to_file(output, argv[1], header);
	ft_free_strarr(output);
	return (0);
}
