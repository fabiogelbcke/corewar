/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/02/10 18:00:07 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */ 

void			invalid_instr(t_routine *head, char **in, char **out, char *line)
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
	ft_putendl(line);
	ft_free_strarr(output);
	ft_free_strarr(input);
	exit(1);
}
