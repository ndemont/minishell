#include "minishell.h"

void	init_data(t_big *datas)
{
	datas->fd = -1;
	datas->flag_pipe = 0;
	datas->env = 0;
	datas->export = 0;
	datas->hidden = 0;
	datas->root = 0;
}

int		main(int ac, char **av, char **env)
{
	t_big	datas;

	(void)ac;
	(void)av;
	init_data(&datas);
	store_env(env, &datas);
	while (read_input(&datas));
	return (0);
}
