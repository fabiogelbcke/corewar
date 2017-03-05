/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhuber <nhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:44:07 by nhuber            #+#    #+#             */
/*   Updated: 2017/03/05 14:33:29 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	eliminate_comments(char *line)
{
	char	*ptr;

	if (ft_strrchr(line, COMMENT_CHAR))
	{
		ptr = ft_strrchr(line, COMMENT_CHAR);
		*ptr = '\0';
	}
	if (ft_strrchr(line, ';'))
	{
		ptr = ft_strrchr(line, ';');
		*ptr = '\0';
	}
}

static char	*multiple_line_comment(char **input, int i, char *str)
{
	int		j;
	int		eoc;
	char	*tmp;
	char	*tmp2;

	eoc = 1;
	i++;
	while (input[i] && eoc < 2)
	{
		j = 0;
		while (input[i][j] && eoc < 2)
		{
			if (input[i][j] == '"')
				eoc++;
			j++;
		}
		tmp = str;
		str = ft_strjoin(str, "\n");
		free(tmp);
		tmp = ft_strnew(j);
		tmp = ft_strncpy(tmp, input[i], j);
		tmp2 = str;
		str = ft_strjoin(str, tmp);
		free(tmp2);
		i++;
	}
	return (str);
}

char	*get_full_comment(char **input, int i, char *begin)
{
	char	*str;
	int		j;
	int		k;
	int		eoc;

	j = ft_strlen(COMMENT_CMD_STRING);
	str = ft_strtrim(begin + j);
	k = 0;
	eoc = 0;
	while (str[k] && eoc < 2)
		eoc += (str[k++] == '"') ? 1 : 0;
	if (eoc == 2)
	{
		if (ft_strlen(str) < 2 || str[0] != '"' || str[ft_strlen(str) - 1] != '"'
				|| ft_strlen(str) > 2 + COMMENT_LENGTH)
		{
			free(str);
			return (NULL);
		}
		return (str);
	}
	str = multiple_line_comment(input, i, str);
	return (str);
}
