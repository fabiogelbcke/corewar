/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/06 13:14:14 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

long int		ft_pow(int base, int exponent)
{
	long int	res;
	int			i;

	res = 1;
	i = 0;
	while (i < exponent)
	{
		if (LONG_MAX / base >= res)
			res = res * base;
		else
		{
			return (0);
		}
		i++;
	}
	return (res);
}

int				get_dir_size(char *cmd)
{
	int			i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(g_op_tab[i].name, cmd))
			return (g_op_tab[i].dir_size == 0 ? 4 : 2);
		i++;
	}
	return (0);
}

int				get_param_size(char *param, char *cmd)
{
	if (param[0] == 'r')
		return (1);
	else if (param[0] == DIRECT_CHAR)
		return (get_dir_size(cmd));
	else
		return (2);
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
	return (int_to_bytecode(dec, 1));
}

char			*get_separator(void)
{
	char		*separator;

	separator = ft_strdup("a");
	separator[0] = SEPARATOR_CHAR;
	return (separator);
}
