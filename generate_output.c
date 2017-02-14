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
	char		*opcode;
	char		*separator;

	i = 0;
	separator = ft_strdup("\0\0");
	separator[0] = SEPARATOR_CHAR;
	while (i < 16)
	{
		if (!ft_strcmp(op_tab[i].name, cmd))
		{
			opcode = int_to_bytecode(op_tab[i].opcode, 1);
			return (ft_strjoin(opcode,  separator));
		}
		i++;
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

char			*get_coding_byte(char **params)
{
	char		**split_line;
	char		*binary;
	int			i;
	char		*separator;
	
	//TODO: NO ACB FOR FORK, ZJMP AND LIVE
	i = 0;
	binary = ft_strdup("");
	while(params[i])
		binary = ft_strjoin(binary, param_code(params[i++]));
	while (ft_strlen(binary) < 8)
		binary = ft_strjoin(binary, "00");
	separator = ft_strdup("\0\0");
	separator[0] = SEPARATOR_CHAR;
	return (ft_strjoin(bin_to_bytecode(binary), separator));
}

void			generate_line(char *input_line, char **line)
{
	char		**split_input;
	char		*cmd;
	char		**params;
	static int	line_pos = 0;

	split_input = ft_split_spaces(input_line);
	cmd = split_input[0];
	params = ft_strsplit(split_input[ft_strarr_len(split_input) - 1], SEPARATOR_CHAR);
	*line = get_opcode(cmd);
	*line = ft_strjoin(*line, get_coding_byte(params));
	*line = ft_strjoin(*line, get_parameters_bytecode(params, cmd, line_pos));
	line_pos += get_bytecodes_count(split_input);
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
