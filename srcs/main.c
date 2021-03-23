#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	while (read_input());
	return (0);
}
