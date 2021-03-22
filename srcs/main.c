#include "minishell.h"

int		main(int ac, char **av)
{
	int 	ret;

	(void)ac;
	(void)av;
	while (read_input());
	return (0);
}
