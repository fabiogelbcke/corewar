/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:48 by fschuber          #+#    #+#             */
/*   Updated: 2017/01/23 18:48:50 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include "libft/Includes/libft.h"
# include "op.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

# define BUF_SIZE 20

typedef struct			s_routine
{
	char				*name;
	int					pos;
	struct s_routine	*next;
}						t_routine;

typedef struct			s_instr
{
	char				*name;
	char				*opcode;
	int					acb;
	
}						t_instr;

typedef struct			s_op
{
	char				*name;
	unsigned int		nbarg;
	char				args_type[MAX_ARGS_NUMBER];
	unsigned int		opcode;
	unsigned int		nbcycles;
	char				*comment;
	char				param_coding;
	char				dir_size;
}						t_op;

extern t_op op_tab[17];

int						is_empty(char *line);
int						is_comment(char *line);
int						is_instruction(char *line);
int						is_name(char *line);
int						is_initial_comment(char *line);
int						is_routine(char *line);
int						valid_initial_comment(char *line);
int						valid_name(char *line);
int						valid_routine(char *line, t_routine *routines);
int						valid_instruction(char *line);
t_routine				*get_routines(char **input);
int						get_param_size(char *param, char *cmd);
int						get_dir_size(char *cmd);
char					*int_to_bytecode(int val, int byte);
int						get_bytecodes_count(char **split_line);
char					**generate_output(char **input, int output_size);
char					*get_parameters_bytecode(char **params, char *cmd, int line_pos, t_routine *routines);
int						has_acb(char *cmd);
int						valid_registry(char *reg);
int						valid_dir_arg(char *dir);
int						valid_ind_arg(char *ind);

#endif
