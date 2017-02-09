#include "asm.h"

int			is_empty(char *line)
{
	char	**split_line;
	
	if (ft_strlen(line) == 0)
		return (1);
	split_line = ft_split_spaces(line);
	if (ft_strarr_len(split_line) == 0)
		return (1);
	return (0);
}

int			is_comment(char *line)
{
	return (!is_empty(line) && line[0] == COMMENT_CHAR)
}

int			is_instruction(char *line)
{
}

int			is_name(char *line)
{
	char	**split_line;
	if (is_empty(line))
		return (0);
	if (!ft_startswith(line, NAME_CMD_STRING))
		return (0);
	
	if (ft_strlen(line) > ft_strlen(NAME_CMD_STRING) + PROG_NAME_LENGTH + 3)
		return (0);
}

int			is_initial_comment(char *line)
{
	return (!is_empty(line) && ft_startswith(line, COMMENT_CMD_STRING));
}

int			is_routine(char *line)
{
	int		is_rout;
	char	**split_line;
	char	*first_word;

	//TODO: CHECK IF NAME IS LABEL_CHARS
	is_rout = !is_empty && !is_comment(line);
	is_rout = is_rout && !is_name(line);
	is_rout = is_rout && !is_initial_comment(line);
	split_line = ft_split_spaces(line);
	first_word = split_line[0];
	is_rout = is_rout && first_word[ft_strlen(first_word) - 2] == LABEL_CHAR;
	return (is_rout);
}
