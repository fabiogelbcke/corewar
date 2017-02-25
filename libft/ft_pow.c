/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/02/10 18:00:07 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int		ft_pow(int base, int exponent)
{
	long int	res;
	int	i;

	res = 1;
	i = 0;
	ft_putnbr(base);
	ft_putendl("");
	ft_putnbr(exponent);
	ft_putendl("");
	while (i < exponent)
	{
		ft_putstr("i = ");
		ft_putnbr(i);
		ft_putendl("");
		if (LONG_MAX / base >= res)
			res = res * base;
		else
		{
			ft_putendl("ops");
			return (0);
		}
		i++;
	}
	ft_putendl ("result:");
	ft_putnbr(res);
	ft_putendl("");
	return res;
}
