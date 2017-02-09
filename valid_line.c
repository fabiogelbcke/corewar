#include "asm.h"

int			valid_initial_comment(char *line)
{
	char	**split_line;

	if (!is_initial_comment(line))
		return (0);
	split_line = ft_split_spaces(line);
	if (ft_strarr_len(split_line) != 2)
		return (0);
	if (ft_strlen(split_line[1]) > COMMENT_LENGTH + 2)
		return (0);
	if (split_line[1][0] != '"' || split_line[1][ft_strlen(split_line[1] - 1)])
		return (0);
	return (1);
}

int			valid_name(char *line)
{
	char	**split_line;

	if (!is_name(line))
		return (0);
	split_line = ft_split_spaces(line);
	if (ft_strarr_len(split_line) != 2)
		return (0);
	if (ft_strlen(split_line[1]) > PROG_NAME_LENGTH + 2)
		return (0);
	if (split_line[1][0] != '"' || split_line[1][ft_strlen(split_line[1] - 1)])
		return (0);
	return (1);
}

int			valid_routine(char *line)
{
	char	**split_line;
	int		i;
	int		j;

	split_line = ft_split_spaces(line);
	i = 0;
	if (ft_strarr_len(split_line) == 0)
		return (0);
	while (split_line[0][i])
	{
		j = 0;
		while (LABEL_CHARS[j])
		{
			if (LABELCHARS[j] == split_line[0][i])
			{
				i++;
				continue
			}
			j++;
		}
		return (0);
	}
	return (1);
}
