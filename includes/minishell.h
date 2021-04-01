#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# include "../libft/libft.h"

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0;0m"

# define CLEAR "\e[H\e[2J"

typedef struct		s_node
{
	int		type;
	char	*input;
	char	**arg;
	char	*ret;
	char	*builtin;
	char	*command;
	char	*left;
	char	*right;
}					t_node;

typedef struct 		s_big
{
	char **env;
}					t_big;

int		read_input(t_big *datas);
t_node	**ft_lexer(char *input);
t_node	**ft_buldin_parser(t_node **token_tab);
void	free_tokens(t_node **token_tab);

#endif
