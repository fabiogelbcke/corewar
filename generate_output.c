/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_output.c                                  :+:      :+:    :+:   */
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
	char		*res;

	i = 0;
	separator = ft_strdup("a");
	separator[0] = SEPARATOR_CHAR;
	while (i < 16)
	{
		if (!ft_strcmp(op_tab[i].name, cmd))
		{
			opcode = int_to_bytecode(op_tab[i].opcode, 1);
			res = ft_strappend_free(opcode, separator);
			return (res);
		}
		i++;
	}
	//Throw error
}

char			*param_code(char *param)
{
	if (param[0] == 'r')
		return ("01");
	else if (param[0] == DIRECT_CHAR)
		return ("10");
	else
		return ("11");
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

char			*get_coding_byte(char **params, char *cmd)
{
	char		**split_line;
	char		*binary;
	int			i;
	char		*separator;
	
	i = 0;
	binary = ft_strdup("");
	if (!has_acb(cmd))
		return (binary);
	while(params[i])
		binary = ft_strjoin(binary, param_code(params[i++]));
	while (ft_strlen(binary) < 8)
		binary = ft_strjoin(binary, "00");
	separator = ft_strdup("a");
	separator[0] = SEPARATOR_CHAR;
	return (ft_strappend_free(bin_to_bytecode(binary), separator));
}



char			*generate_line(char *input_line, t_routine *routines)
{
	char		**split_input;
	char		*cmd;
	char		**params;
	static int	line_pos = 0;
	char		*line;
	char		**awe;
	int			i;

	split_input = ft_split_spaces(input_line);
	cmd = split_input[0];
	awe = ft_strsplit(split_input[ft_strarr_len(split_input) - 1], SEPARATOR_CHAR);
	params = get_params(split_input);
	line = get_opcode(cmd);
	line = ft_strappend_free(line, get_coding_byte(params, cmd));
	line = ft_strappend_free(line, get_parameters_bytecode(params, cmd, line_pos, routines));
	line_pos += get_bytecodes_count(split_input);
	ft_free_strarr(split_input);
	ft_free_strarr(params);
	return (line);
}

void			exit_invalid_instruction(t_routine *head, char **input, char **output, char *line)
{
	t_routine	*next;

	while (head != NULL)
	{
		next = head->next;
		free(head->name);
		free(head);
		head = next;
	}
	ft_putendl(line);
	ft_putendl("Invalid instruction");
	ft_free_strarr(input);
	ft_free_strarr(output);
	exit(1);
}

char			**generate_output(char **input, int output_size)
{
	t_routine	*routines;
	int			i;
	int			j;
	char		**output;

	routines = get_routines(input);
	i = 0;
	j = 0;
	output = ft_memalloc(output_size * sizeof(char));
	while (input[i])
	{
		if (is_instruction(input[i]))
		{
			if (valid_instruction(input[i]))
				output[j++] = generate_line(input[i], routines);
			else
				exit_invalid_instruction(routines, output, input, input[i]);
		}
		i++;
	}
	output[j] = NULL;
	return output;
}
