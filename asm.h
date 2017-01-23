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
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct		s_routine
{
	char			*name;
	int				pos;
}					t_routine;

typedef struct		s_instr
{
	char			*name;
	char			*opcode;
	int				acb;
	
}
