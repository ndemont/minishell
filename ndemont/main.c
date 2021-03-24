#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
	return (0);
}

int		ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}	

int		is_op(char c)
{
	if (c == '+')
		return (1);
	if (c == '-')
		return (1);
	if (c == '/')
		return (1);
	if (c == '%')
		return (1);
	if (c == '*')
		return (1);
	else
		return (0);
}

t_tree *new_digit_elem(char c, t_tree **tree)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (!new)
		print_error("Malloc");
	new->op = 0;
	*new->value = c - 48;
	new->leftchild = 0;
	new->rightchild = 0;
	return (new);	
}

t_tree *new_op_elem(char c, t_tree **tree)
{
	t_tree *new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (!new)
		print_error("Malloc");
	*new->op = c;
	new->value = 0;
	new->leftchild = 0;
	new->rightchild = 0;
	return (new);	
}

t_tree	**create_tree(char **av, int ac)
{
	int			i;
	t_tree		**tree;
	t_tree		*new;
	static char	*op = "+-/%*";
	
	tree = 0;
	i = 1;
	while (i < ac)
	{
		printf("%i\n", i);
		printf("before digit test\n");
		if (ft_isdigit(av[i][0]))
		{
			new = new_digit_elem(av[i][0], tree);
			printf("new digit created\n");
		}
		else if (is_op(av[i][0]))
			new = new_op_elem(av[i][0], tree);
		else
			return (0);
		printf("before next loop\n");
		i++;
	}
	return (tree);
}

int		resolve_tree(t_tree **tree)
{
	return (1);
}

int 	main(int ac, char **av)
{
	int		rslt;
	int		i;
	t_tree	**tree;
	
	if (ac == 1)
		return (0);
	tree = create_tree(av, ac);
	rslt = resolve_tree(tree);
	i = 1;
	while (i < ac)
	{
		printf("%s ", av[i]);
		i++;
	}
	printf("%d\n", rslt);
	return (0);
}
