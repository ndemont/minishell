#include "minishell.h"

int		main(int ac, char **av)
{
	int ret;

	(void)ac;
	(void)av;
	printf(minishellrose);
	while (ret = read(0, 0_RDONLY))
	{
		printf($);
	}
	return (0);
}
