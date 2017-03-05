/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/05 17:44:33 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		invalid_instr(t_routine *head, char **in, char **out, char *l)
{
	t_routine	*next;

	while (head != NULL)
	{
		next = head->next;
		free(head->name);
		free(head);
		head = next;
	}
	ft_putstr("Invalid instruction : ");
	ft_putendl(l);
	ft_free_strarr(out);
	ft_free_strarr(in);
	exit(1);
}

int			invalid_usage(int i)
{
	ft_putendl("Usage: ./asm <sourcefile.s>");
	if (i < 0)
	{
		ft_putstr("\tInvalid number of arguments : ");
		ft_putnbr(i * -1);
		ft_putchar('\n');
	}
	return (-1);
}

char 		**invalid_arg(char **input)
{
	if (input != NULL)
		free(input);
	invalid_usage(0);
	return (NULL);
}

int			invalid_ext(char *path)
{
	int er;

	er = 0;
	if (path[ft_strlen(path) - 1] != 's' &&
			path[ft_strlen(path) - 2] != '.')
	{
		er = invalid_usage(0);
		ft_putendl("\tInvalid file extension");
	}
	return (er);
}
