/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/05 17:27:47 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			**get_next_input(int fd)
{
	int		i;
	char	**input;
	int		total_size;
	int		ret;

	i = 0;
	total_size = BUF_SIZE;
	if ((input = (char **)ft_memalloc(sizeof(char *) * BUF_SIZE)) == NULL)
		return (NULL);
	while ((ret = ft_gnl(fd, &(input[++i - 1]))) > 0)
	{
		if (i == total_size - 1)
		{
			if ((input = realloc(input, sizeof(char*) *
							(total_size + BUF_SIZE))) == NULL)
				return (NULL);
			total_size += BUF_SIZE;
		}
	}
	if (i == 1 && ret == -1)
		return (invalid_arg(input));
	input[i] = NULL;
	return (input);
}

char			**get_input(char *filename)
{
	char	**input;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (NULL);
	input = get_next_input(fd);
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
		return (invalid_usage(argc * -1));
	if ((input = get_input(argv[1])) == NULL)
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
