/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/03 11:12:42 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			**get_input(char *filename)
{
	char		**input;
	int			total_size;
	int			i;
	int			fd;

	if ((input = (char **)ft_memalloc(sizeof(char *) * BUF_SIZE)) == NULL)
		return (NULL);
	total_size = BUF_SIZE;
	i = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		free(input);
		return (NULL);
	}
	while (++i)
	{
		if (ft_gnl(fd, &(input[i - 1])) == 0)
			break ;
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

int				get_output_size(char **output)
{
	int			i;
	int			size;
	int			j;

	i = 0;
	size = 0;
	while (output[i])
	{
		j = 0;
		while (output[i][j])
		{
			if (output[i][j] == ',')
				size++;
			j++;
		}
		if (j > 0)
			size++;
		i++;
	}
	return (size);
}

int				main(int argc, char **argv)
{
	char		**input;
	char		**output;
	t_header	header;
	int			prog_start;

	if (argc < 2)
		return (-1);
	input = get_input(argv[1]);
	if (!input)
	{
		perror(NULL);
		exit(1);
	}
	header = get_header(input, &prog_start);
	if (prog_start == 0)
	{
		ft_putendl("Invalid header");
		ft_free_strarr(input);
		exit(1);
	}
	output = generate_output(input, ft_strarr_len(input), prog_start);
	ft_free_strarr(input);
	header.prog_size = get_output_size(output);
	print_to_file(output, argv[1], header);
	ft_free_strarr(output);
	return (0);
}
