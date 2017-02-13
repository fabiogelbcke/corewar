/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/02/10 18:00:07 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ 

#include "asm.h"

void	generate_line(char *input_line, char **line)
{
	static int curr_pos = 0;	
}



void	generate_output(char **input, char **output)
{
	t_routine *routines;

	routines = get_routines(input);
	while (routines)
	{
		ft_putendl("routine:");
		ft_putendl(routines->name);
		ft_putnbr(routines->pos);
		ft_putendl("");
		routines = routines->next;
	}
}

int		main(int argc, char **argv)
{
	int		fd;
	char	**input;
	char	**output;
	int		i;
	int		total_size;
	
	if (argc < 2)
		return -1;
	input = ft_memalloc(BUF_SIZE * sizeof(char*));
	total_size = BUF_SIZE;
	i = 0;
	fd = open(argv[1], O_RDONLY);
	while (++i)
	{
		if (ft_gnl(fd, &(input[i - 1])) == 0)
			break;
		if (i == total_size - 1)
		{
			input = ft_realloc(input, (total_size + BUF_SIZE) * sizeof(char*), total_size * sizeof(char*));
			if (input == NULL)
				return -1;
			total_size += BUF_SIZE;
		}
	}
	input[i] = NULL;
	output = ft_memalloc(i * sizeof(char*));
	generate_output(input, output);
}
