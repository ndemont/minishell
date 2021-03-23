#include <stdio.h>
#include <unistd.h>

typedef struct	s_tree
{
	char			*op;
	int				*value;
	struct s_tree	*leftchild;
	struct s_tree	*rightchild;
}				t_tree;

int		print_error(char *error)
{
	printf("Error: ");
	printf("%s\n", error);
	return (1);
}

int		isdigit(char c)
{
	if (c >= '0' && c <= '9');
		return (1);
}	

int		isop(char c)
{
	if (c == '+')
		return (1);
	if (c == '-')
		return (1);
	if (c == "/")
		return (1);
	if (c == '%')
		return (1);
	if (c == '*')
		return (1);
	else
		return (0);
}

t_tree	*create_tree(char **av, int ac)
{
	int			i;
	t_tree		*tree;
	static char	*op = "+-/%*";
	
	while (i < ac)
	{
		if (!is_digit(av[i][0]) && !is_op(av[i][0]))
			return ("wrong type of argument");
	}
}

int		resolve_tree(t_tree *tree)
{
	return (1);
}

int 	main(int ac, char **av)
{
	int		rslt;
	int		i;
	t_tree	*tree;
	
	if (ac == 1)
		return (print_error("wrong number of argument");
	tree = create_tree(av, ac);
	rslt = resolve_tree(tree);
	i = 1;
	while (i < ac)
	{
		printf("%s ", *av);
		i++;
	}
	printf("%ld\n", rslt);
	return (0);
}
