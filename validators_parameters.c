/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators_parameters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/02/10 18:00:07 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		valid_registry(char *reg)
{
	int	i;
	int	val;

	if (!reg || !reg[0] || reg[0] != 'r' || !ft_isnbr(&reg[1]))
		return (0);
	val = ft_atoi(&reg[1]);
	return (val > 0 && val <= REG_NUMBER);
}

int		valid_label(char *label)
{
	int	i;
	int	j;

	if (!label[0] || label[0] != LABEL_CHAR)
		return (0);
	i = 1;
	while (label[i])
	{
		j = 0;
		while (LABEL_CHARS[j])
		{
			if (LABEL_CHARS[j] == label[i])
			{
				i++;
				break ;
			}
			j++;
		}
		if (!LABEL_CHARS[j])
		{

			return (0);
		}
	}
	return (1);
}

int		valid_dir_arg(char *dir)
{
	if (!dir || !dir[0] || !dir[1] || dir[0] != DIRECT_CHAR)
		return (0);
	if (dir[1] == LABEL_CHAR)
		return (valid_label(&dir[1]));
	if (ft_strlen(dir) >= 3 && dir[1] == '-' && ft_isnbr(&dir[2]))
		return (1);
	return (ft_isnbr(&dir[1]));
}

int		valid_ind_arg(char *ind)
{
	if (!ind || !ind[0])
		return (0);
	if (ind[0] == LABEL_CHAR)
		return (valid_label(ind));
	if (ft_strlen(ind) >= 3 && ft_isnbr(&ind[1]) && ind[0] == '-')
		return (1);
	return (ft_isnbr(ind));
}
