/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhuber <nhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:44:07 by nhuber            #+#    #+#             */
/*   Updated: 2017/03/06 13:22:54 by nhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		eliminate_comments(char *line)
{
	char	*ptr;

	while (ft_strrchr(line, COMMENT_CHAR))
	{
		ptr = ft_strrchr(line, COMMENT_CHAR);
		*ptr = '\0';
	}
	while (ft_strrchr(line, ';'))
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
	while (input[++i] && eoc < 2)
	{
		j = 0;
		while (input[i][j] && eoc < 2)
			eoc += (input[i][j++] == '"') ? 1 : 0;
		tmp = str;
		str = ft_strjoin(str, "\n");
		free(tmp);
		tmp = ft_strnew(j);
		tmp = ft_strncpy(tmp, input[i], j);
		tmp2 = str;
		str = ft_strjoin(str, tmp);
		free(tmp2);
	}
	return (str);
}

char		*get_full_comment(char **input, int i, char *begin)
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
		if (ft_strlen(str) < 2 || str[0] != '"' ||
				str[ft_strlen(str) - 1] != '"' ||
				ft_strlen(str) > 2 + COMMENT_LENGTH)
		{
			free(str);
			return (NULL);
		}
		return (str);
	}
	str = multiple_line_comment(input, i, str);
	return (str);
}

static char	*full_comment_form(char *str)
{
	int		i;
	int		j;
	char	*ret;

	if (!(ret = (char *)malloc(sizeof(char) * ft_strlen(str) - 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"')
			ret[j++] = str[i];
		i++;
	}
	ret[j] = '\0';
	free(str);
	return (ret);
}

int			add_full_comment(t_header *header, char **input, int i)
{
	char	*begin;
	char	*tmp;
	int		eoc;
	int		j;
	int		ret;

	begin = ft_strtrim(input[i]);
	tmp = get_full_comment(input, i, begin);
	free(begin);
	tmp = full_comment_form(tmp);
	ft_strcpy((*header).comment, tmp);
	free(tmp);
	eoc = 0;
	ret = i;
	while (eoc < 2 && input[i])
	{
		j = 0;
		while (input[i][j] && eoc < 2)
			eoc += (input[i][j++] == '"') ? 1 : 0;
		i++;
	}
	return (i - ret);
}
