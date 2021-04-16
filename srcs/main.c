#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	t_big	datas;

	(void)ac;
	(void)av;
	store_env(env, &datas);
	while (read_input(&datas));
	return (0);
}
