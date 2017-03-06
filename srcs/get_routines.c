/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_routines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:48 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/06 11:39:42 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_routine		*create_routine(char *name, int pos)
{
	t_routine	*new_rout;

	new_rout = malloc(sizeof(t_routine));
	new_rout->name = ft_strdup(name);
	new_rout->pos = pos;
	return (new_rout);
}

void			exit_bad_routine(t_routine *head, char **input, char *rout)
{
	t_routine	*next;

	while (head != NULL)
	{
		next = head->next;
		free(head->name);
		free(head);
		head = next;
	}
	ft_putstr(rout);
	ft_putendl(" : Invalid or repeated label");
	ft_free_strarr(input);
	exit(1);
}

int				increase_pos(char *line)
{
	int		pos;
	char	**split_line;

	split_line = ft_split_spaces(line);
	pos = get_bytecodes_count(split_line);
	ft_free_strarr(split_line);
	return (pos);
}

t_routine		*get_routines(char **input, int i, int pos)
{
	t_routine	*last;
	t_routine	*curr;
	char		**split_line;

	last = NULL;
	curr = NULL;
	while (input[++i])
	{
		eliminate_comments(input[i]);
		if (is_routine(input[i]))
		{
			split_line = ft_split_spaces(input[i]);
			split_line[0][ft_strlen(split_line[0]) - 1] = '\0';
			if (!valid_routine(split_line[0], last))
				exit_bad_routine(last, input, split_line[0]);
			curr = create_routine(split_line[0], pos);
			curr->next = last;
			last = curr;
			free(input[i]);
			input[i] = ft_join_strarr(&split_line[1], ' ');
			ft_free_strarr(split_line);
		}
		pos += (is_instruction(input[i])) ? increase_pos(input[i]) : 0;
	}
	return (curr);
}
