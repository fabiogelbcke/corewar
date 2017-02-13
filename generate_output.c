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

char			*get_opcode(char *cmd)
{
	int			i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(op_tab[i].name, cmd))
			return (ft_strjoin(int_to_bytecode(op_tab[i].nbarg, ",")));
	}
	//Throw error
}

char			*get_coding_byte(char *line)
{

}

void			generate_line(char *input_line, char **line)
{
	static int	curr_pos = 0;
	static int	line_pos = 0;
	int			i;

	*line = get_opcode(ft_split_spaces(input_line)[0]);
	*line = ft_strjoin(*line, get_coding_byte(input_line));
}

void			generate_output(char **input, char **output)
{
	t_routine	*routines;
	int			i;
	int			j;

	routines = get_routines(input);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (is_instruction(input[i]) && valid_instruction(input[i]))
			generate_line(input[i], &output[j++]);
		i++;
	}
}
