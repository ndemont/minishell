#include "minishell.h"

void	actualize_data(t_big *datas)
{
	datas->fd = -1;
	datas->flag_pipe = 0;
	datas->flag_bracket = 0;
	datas->flag_left_bracket = 0;
	datas->quit = 0;
	datas->root = 0;
}

void	init_data(t_big *datas)
{
	datas->fd = -1;
	datas->flag_pipe = 0;
	datas->flag_bracket = 0;
	datas->flag_left_bracket = 0;
	datas->redirection_arg = 0;
	datas->env = 0;
	datas->quit = 0;
	datas->export = 0;
	datas->hidden = 0;
	datas->root = 0;
}

void	sigint_handler(int sig)
{
	(void)sig;
}

int		main(int ac, char **av, char **env)
{
	t_big	datas;

	(void)ac;
	(void)av;
	init_data(&datas);
	store_env(env, &datas);
	signal(SIGINT, &sigint_handler);
	while (read_input(&datas));
	return (0);
}
