#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	t_big	datas;

	(void)ac;
	(void)av;
	store_env(env, &datas);
	//while(datas.env)
	//{
	//	printf("VAR = %s || ", ((t_var *)datas.env->content)->var);
	//	printf("VALUE = %s\n", ((t_var *)datas.env->content)->value);
	//	datas.env = datas.env->next;
	//}
	while (read_input(&datas));
	return (0);
}
