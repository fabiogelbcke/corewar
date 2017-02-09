#include "libft/Includes/libft.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	int i = 0;
	char **split = ft_split_spaces(" faaaaabii		o fabiosidid ajajha     aiaiai aiaiaia ultimo");

	while (split[i])
	{
		ft_putstr(split[i]);
		ft_putchar('\n');
		i++;
	}
	return (1);
}
