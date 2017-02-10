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

int						is_empty(char *line);
int						is_comment(char *line);
int						is_instruction(char *line);
int						is_name(char *line);
int						is_initial_comment(char *line);
int						is_routine(char *line);
int						valid_initial_comment(char *line);
int						valid_name(char *line);
int						valid_routine(char *line);


#endif
