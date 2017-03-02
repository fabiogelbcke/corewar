/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:49:50 by fschuber          #+#    #+#             */
/*   Updated: 2017/03/02 13:48:03 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	numberofwords(char const *s)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if ((s[i] != ' ' && s[i] != SEPARATOR_CHAR)
			&& (i == 0 || s[i - 1] == ' ' || s[i - 1] == SEPARATOR_CHAR))
			n++;
		i++;
	}
	return (n);
}

static int	getsize(int *i, const char *s, int size)
{
	while (s[*i] == ' ' || s[*i] == SEPARATOR_CHAR)
		(*i)++;
	while (s[*i + size] != ' '
			& s[*i + size] != SEPARATOR_CHAR && s[*i + size])
		size++;
	return (size);
}

char		**get_split_params(char const *s)
{
	char	**table;
	int		i;
	int		k;
	int		size;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	table = (char **)malloc(sizeof(char*) * (numberofwords(s) + 1));
	if (!table)
		return (NULL);
	while (k < numberofwords(s))
	{
		size = getsize(&i, s, 0);
		table[k] = (char*)malloc((size + 1) * sizeof(char));
		i--;
		size = 0;
		while (s[++i] != ' ' && s[i] != SEPARATOR_CHAR && s[i])
			table[k][size++] = s[i];
		table[k++][size] = '\0';
	}
	table[k] = NULL;
	return (table);
}

char		**get_params(char **split_input)
{
	char	*params;
	char	**split_params;

	if (!split_input || !split_input[0] || !split_input[1])
		return (NULL);
	params = ft_join_strarr(&split_input[1], ',');
	split_params = ft_strsplit(params, ',');
	free(params);
	return (split_params);
}
