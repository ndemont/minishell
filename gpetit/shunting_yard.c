
#include "../includes/minishell.h"

typedef struct		s_shunt
{
	void			*content;
	char			type;				
	struct s_shunt	*next;
}					t_shunt;

void	free_array(t_shunt *polish)
{
	t_shunt *tmp;

	while (polish)
	{
		tmp = polish;
		polish = (polish)->next;
		free(tmp->content);
		free(tmp);
	}
}

void	print_array(t_shunt *polish)
{
	t_shunt *tmp;

	tmp = polish;
	while (tmp)
	{
		if (tmp->type == 'c')
			printf("%c", *((char *)tmp->content));
		else if (tmp->type == 'i')
			printf("%i", *((int *)tmp->content));
		printf(" ");
		tmp = tmp->next;
	}
	printf("\n");
}

t_shunt	*ft_lstnew_type(void *content, char type)
{
	t_shunt	*new;

	new = malloc(sizeof(t_shunt));
	if (!new)
		return (NULL);
	new->content = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_front_type(t_shunt **alst, t_shunt *new)
{
	new->next = *alst;
	*alst = new;
}

void	ft_lstadd_back_type(t_shunt **alst, t_shunt *new)
{
	t_shunt	*lst;

	if (!alst)
		return ;
	lst = *alst;
	if (!lst)
	{
		*alst = new;
		return ;
	}
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

int		rank(char c)
{
	if (c == '+' || c == '-')
		return (1);
	else if (c == '*' || c == '/')
		return (2);
	else
		return (-1);
}

void	push(char c, t_shunt **stack, char type)
{
	t_shunt *new;
	char *content;

	content = (char*)malloc(sizeof(char));
	*content = c;
	new = ft_lstnew_type(content, type);
	if (!(*stack))
		*stack = new;
	else
		ft_lstadd_front_type(stack, new);
}

void	pop(t_shunt **polish, t_shunt **stack)
{
	t_shunt *tmp;

	tmp = *stack;
	*stack = (*stack)->next;
	tmp->next = NULL;
	ft_lstadd_back_type(polish, tmp);
}

void	queue(t_shunt **polish, char *nbr)
{
	int *content;
	t_shunt *new;

	content = (int *)malloc(sizeof(int));
	*content = ft_atoi(nbr);
	new = ft_lstnew_type(content, 'i');
	if (!polish)
		*polish = new;
	else
		ft_lstadd_back_type(polish, new);
}

t_shunt	*reverse_polish(char *str)
{
	t_shunt *polish;
	t_shunt *stack;
	int i = 0;

	polish = NULL;
	stack = NULL;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			queue(&polish, str + i);
			while (str[i + 1] && ft_isdigit(str[i + 1]))
				i++;
		}
		else if (ft_strchr( "+-*/", str[i]))
		{
			if (stack && rank(str[i]) < rank(*(char *)stack->content))
			{
				while (stack && rank(str[i]) < rank(*(char *)stack->content))
					pop(&polish, &stack);
				push(str[i], &stack, 'c');
			}
			else
				push(str[i], &stack, 'c');
		}
		i++;
	}
	while (stack)
		pop(&polish, &stack);
	return (polish);
}

int		solver(t_shunt *polish)
{
	t_shunt *stack;

	while (polish)
	{
		if (polish->type == 'c')
		else if (polish->type == '')
		
		polish = polish->next;
	}
}

void	shunting_yard(char *str)
{
	t_shunt	*polish;
	int		solution;
	
	polish = reverse_polish(str);
	print_array(polish);
	solution = solver(polish);
	free_array(polish);
}

int main(int ac, char **av)
{
	if (ac != 2)
		printf("Wrong Number of arguments");
	else
		shunting_yard(av[1]);
	return (0);
}
