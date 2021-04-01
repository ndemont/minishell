#include "minishell.h"

void	store_env(char **env, t_big *datas)
{
	int k;

	k = 0;
	while (env[k])
		k++;
	datas->env = (char **)malloc(sizeof(char *) * (k + 1));
	k = 0;
	while (env[k])
	{
		datas->env[k] = ft_strdup(env[k]);
		k++;
	}
	datas->env[k] = NULL;
}

int		main(int ac, char **av, char **env)
{
	t_big datas;

	(void)ac;
	(void)av;
	(void)env;
	//store_env(env, &datas);
	while (read_input(&datas));
	return (0);
}
