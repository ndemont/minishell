#include "../includes/minishell.h"

int main(void)
{
	char *str;

	str = ft_strdup("helloJoliefille");
	printf("ADDRESS OF STR = [%p]\n", str);
	printf("CONTENT OF STR = [%s]\n", str);
	clean_free(&str);
	printf("ADDRESS OF STR = [%p]\n", str);
	printf("CONTENT OF STR = [%s]\n", str);
	return(0);
}
