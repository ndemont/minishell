#include "minishell.h"

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	while (read_input());
	return (0);
}
