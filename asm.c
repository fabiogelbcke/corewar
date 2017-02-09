/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/01/23 19:22:08 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ 

#include "asm.h"

void	generate_line(char *input_line, char **line)
{
	static int curr_pos = 0;

	
}

int			get_bytecodes_count(char **split_line)
{
	int		count;
	int		sl_len;
	int		i;

	sl_len = ft_strarr_len(split_line);
	if (sl_len == 0)
		return (0);
	count = 2;
	params = ft_strsplit(split_line[sl_len - 1], ',');
	sl_len = ft_strarr_len(params);
	if (sl_len == 0)
		return (count);
	i = 0;
	while (params[i])
	{
		
	}
}

t_routine	*get_routines(char **input)
{
	int		i;
	t_routine *head;

	i = 0;
	while (input[i])
	{
		split_line = ft_split_spaces(input[i]);
		if (split_line[0])
		{
			if (split_line[0][ft_strlen(split_line[0]) -2] == ':')
			
		}
	}

}

void	generate_output(char **input, char **output)
{
	t_routine *routines = get_routines();
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
		ft_putnbr(i);
		if (ft_gnl(fd, &(input[i - 1])) == 0)
			break;
		ft_putnbr(i);
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
	get_output(input, output);
}
