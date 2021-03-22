#include "minishell.h"

int		main(int ac, char **av)
{
	int ret;

	printf("minishellrose");
	while (ret = read(0, 0_RDONLY))
	{	
		printf("$");
	}
	return (0);
}
