/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:48 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/05 14:16:00 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include "../libft/Includes/libft.h"
# include "op.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

# define BUF_SIZE COMMENT_LENGTH

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

extern t_op				g_op_tab[17];

int						is_empty(char *line);
int						is_comment(char *line);
int						is_instruction(char *line);
int						is_name(char *line);
int						is_initial_comment(char *line);
int						is_routine(char *line);
int						valid_initial_comment(char **line, int i);
int						valid_name(char *line);
int						valid_routine(char *line, t_routine *routines);
int						valid_instruction(char *line);
int						valid_registry(char *reg);
int						valid_dir_arg(char *dir);
int						valid_ind_arg(char *ind);
char					*get_full_comment(char **input, int i, char *begin);
char 					*get_label_param(char *param, int line_pose,
							int size, t_routine *routine);
t_routine				*get_routines(char **input, int i, int pos);
int						get_param_size(char *param, char *cmd);
int						get_dir_size(char *cmd);
char					*get_parameters_bytecode(char **params, char *cmd,
										int line_pos, t_routine *routines);
int						get_bytecodes_count(char **split_line);
t_header				get_header(char **input, int *prog_start);
char					*int_to_bytecode(long int val, int byte);
char					**generate_output(char **input, int output_size,
											int prog_start);
int						has_acb(char *cmd);
void					print_to_file(char **output, char *filename,
										t_header header);

char					*get_file_name(char *filename);
char					**get_params(char **split_input);
char					*bin_to_bytecode(char *bin);
void					invalid_instr(t_routine *head, char **in,
										char **out, char *l);
long int				ft_pow(int base, int exponent);
void					free_routines(t_routine *routines);
void					eliminate_comments(char *line);

#endif
