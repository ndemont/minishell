
#include "../includes/minishell.h"

int		rank(char c)
{
	if (c = '+' || c = '-')
		return (1);
	else if (c = '*' || c = '/')
		return (2);

void	push(char c, t_list **stack)
{
	t_list *new;
	char *content;

	content = (char*)malloc(sizeof(char));
	*content = c;
	if (!(*stack))
		*stack = ft_lstnew(content);
	else
	{
		new = ft_lstnew(content);
		ft_lstadd_front(stack, new);
	}
}

void	pop(char **polish, t_list **stack)
{
	t_list *tmp;

	*polish = (*stack)->content;
	tmp = *stack;
	stack = (*stack)->next;
	free(tmp->content);
	free(tmp);
}

void	queue(char **polish, char c)
{
	*polish = c;
}

char	*reverse_polish(char *str)
{
	char *polish;
	t_list *stack;
	int i = 0;
	int j = 0;

	polish = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			queue(&(polish[j++]), str[i]);
		else if (ft_strchr(str[i], "+-*/"))
		{
			if (stack && rank(str[i]) < rank(stack->content))
			{
				pop(&(polish[j++]), stack);
				push(str[i], stack);
			}
			else
				push(str[i], stack);
		}
		i++;
	}
	while (stack)
	{
		pop(&(polish[j++]), stack);
		stack = stack->next;
	}
	polish[j] = '\0';
}

void	shunting_yard(char *str)
{
	char *polish;
	
	polish = reverse_polish(str);
	ft_putstr(polish);
}

int main(int ac, char **av)
{
	(void)ac;
	shunting_yard(av[1]);
	return (0);
}
