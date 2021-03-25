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

int		ft_aredigit(char *str)
{
	int i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}	

int		is_op(char c)
{
	if (c == '+')
		return (1);
	if (c == '-')
		return (1);
	if (c == '/')
		return (2);
	if (c == '%')
		return (2);
	if (c == '*')
		return (2);
	else
		return (0);
}

void	ft_treeadd_back(t_tree **tree, t_tree *new)
{
	t_tree	*lst;

	if (!tree)
		return ;
	lst = *tree;
	if (!lst)
	{
		*tree = new;
		return ;
	}
	while (lst->rightchild)
		lst = lst->rightchild;
	lst->rightchild = new;
}

t_tree *new_digit_elem(char *c)
{
	t_tree	*new;
	int		*nb;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (!new)
		print_error("Malloc");
	nb = (int *)malloc(sizeof(int));
	*nb = atoi(c);
	new->op = 0;
	new->value = nb;
	new->leftchild = 0;
	new->rightchild = 0;
	return (new);	
}

t_tree *new_op_elem(char *c)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (!new)
		print_error("Malloc");
	new->op = c;
	new->value = 0;
	new->leftchild = 0;
	new->rightchild = 0;
	return (new);	
}

t_tree	**create_tree(t_tree **tree)
{
	t_tree **root;
	int i;

	root = (t_tree **)malloc(sizeof(t_tree));
	i = 0;
	root = &tree[i];
	i++;
	while (tree[i])
	{
		if (is_op(*tree[i]->op) == 1)
		{
			tree[i]->leftchild = *root;
			root = &tree[i];
		}
		else if (is_op(*tree[i]->op) == 2)
		{
			tree[i - 1]->rightchild = tree[i];
		}
		i++;
	}
	return (root);
}

int		resolve_tree(t_tree *tree)
{
	if (tree->value)
		return (*tree->value);
	if (*tree->op == '+')
		return (resolve_tree(tree->leftchild) + resolve_tree(tree->rightchild));
	if (*tree->op == '-')
		return (resolve_tree(tree->leftchild) - resolve_tree(tree->rightchild));
	if (*tree->op == '*')
		return (resolve_tree(tree->leftchild) * resolve_tree(tree->rightchild));
	if (*tree->op == '/')
		return (resolve_tree(tree->leftchild) / resolve_tree(tree->rightchild));
	if (*tree->op == '%')
		return (resolve_tree(tree->leftchild) % resolve_tree(tree->rightchild));
	return (0);
}

t_tree	**create_tokenlist(int ac, char **av)
{
	int		i;
	t_tree	*left;
	t_tree	*right;
	int		j;
	t_tree	**tokens;

	tokens = malloc(sizeof(t_tree) * ac);
	i = 1;
	j = 0;
	while (i < ac - 1)
	{
		if (!ft_aredigit(av[i]))
			return (0);
		left = new_digit_elem(av[i]);
		i++;
		if (!is_op(av[i][0]))
			return (0);
		tokens[j] = new_op_elem(av[i]);
		i++;
		if (!ft_aredigit(av[i]))
			return (0);
		right = new_digit_elem(av[i]);
		tokens[j]->leftchild = left;
		tokens[j]->rightchild = right;
		j++;
	}
	tokens[j] = 0;
	return (tokens);
}

int 	main(int ac, char **av)
{
	int		i;
	int		rslt;
	t_tree	**root;
	t_tree	**token_list;
	
	if (ac == 1)
		return (0);
	i = 1;
	while (i < ac)
	{
		printf("%s ", av[i]);
		i++;
	}
	printf("\n\n");
	token_list = create_tokenlist(ac, av);
	i = 0;
	while (token_list[i])
	{
		printf("%i ", *(token_list[i])->leftchild->value);
		printf("%c ", *(token_list[i])->op);
		printf("%i\n", *(token_list[i])->rightchild->value);
		i++;;
	}
	root = create_tree(token_list);
	rslt = resolve_tree(*root);
	printf("\n%d\n", rslt);
	return (0);
}
