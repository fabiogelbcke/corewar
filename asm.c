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

int			get_param_size(char *param)
{
	if (param[0] == 'r')
		return REG_SIZE;
	else if (param[0] == LABEL_CHAR)
		return DIR_SIZE;
	else
		return IND_SIZE;
}

int			get_bytecodes_count(char **split_line)
{
	int		count;
	int		sl_len;
	int		i;
	char	**params;

	sl_len = ft_strarr_len(split_line);
	if (sl_len == 0)
		return (0);
	count = 2;
	params = ft_strsplit(split_line[sl_len - 1], SEPARATOR_CHAR);
	sl_len = ft_strarr_len(params);
	if (sl_len == 0)
		return (count);
	i = 1;
	while (params[i])
	{
		count += get_param_size(params[i]);
		i++;
	}
	return (count);
}

t_routine	*create_routine(char *name, int pos)
{
	t_routine *new_rout;

	ft_putendl(name);
	ft_putnbr(pos);
	ft_putchar('\n');
	new_rout = malloc(sizeof(t_routine));
	new_rout->name = ft_strdup(name);
	new_rout->pos = pos;
	return new_rout;
}

t_routine	*get_routines(char **input)
{
	int		i;
	t_routine *last;
	t_routine *curr;
	int		pos;
	char	**split_line;

	i = 0;
	last = NULL;
	pos = 0;
	while (input[i])
	{
		if (is_routine(input[i]))
		{
			split_line = ft_split_spaces(input[i]);
			curr = create_routine(split_line[0], pos);
			curr->next = last;
			last = curr;
			input[i] = ft_join_strarr(&split_line[1], ' ');
		}
		pos += get_bytecodes_count(ft_split_spaces(input[i]));
		i++;
	}
	return curr;
}

void	generate_output(char **input, char **output)
{
	t_routine *routines;

	routines = get_routines(input);
	/*while (routines)
	{
		ft_putendl("routine:");
		ft_putendl(routines->name);
		ft_putnbr(routines->pos);
		routines = routines->next;
		}*/
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
