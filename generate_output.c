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

char			*param_code(char *param)
{
	if (param[0] == 'r')
		return (ft_strdup("01"));
	else if (param[0] == DIRECT_CHAR)
		return (ft_strdup("10"));
	else
		return (ft_strdup("11"));
}

char			*bin_to_bytecode(char *bin)
{
	int			dec;
	int			i;
	int			mult;

	dec = 0;
	i = ft_strlen(bin) - 1;
	mult = 1;
	while (i >= 0)
	{
		dec += (bin[i] - 48) * mult;
		mult = mult * 2;
		i--;
	}
	return int_to_bytecode(dec, 1);
}

char			*get_coding_byte(char *line)
{
	char		**split_line;
	char		**params;
	char		*binary;
	int			i;
	
	//TODO: NO ACB FOR FORK, ZJMP AND LIVE
	split_line = ft_split_spaces(line);
	params = ft_strsplit(split_line[sl_len - 1], SEPARATOR_CHAR);
	i = 0;
	binary = ft_strdup("");
	while(params[i])
		binary = ft_strjoin(binary, param_code(params[i++]));
	while (ft_strlen(binary) < 8)
		binary = ft_strjoin(binary, "00");
	return (ft_strjoin(bin_to_bytecode(binary), ","));
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
