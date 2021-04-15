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
	int				type;
	char			*input;
	char			**arg;
	char			*ret;
	char			*builtin;
	char			*command;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct		s_var
{
	char *var;
	char *value;
}					t_var;

typedef struct 		s_big
{
	int		fd;
	int		flag_pipe;
	t_list	**env;
	t_list	**export;
	t_list	**hidden;
	t_node	*root;
}					t_big;

//ENV
int			ft_env(t_big *datas);
void		store_env(char **env, t_big *datas);

//AST
int			read_input(t_big *datas);
t_node		**ft_lexer(char *input);
t_node		**ft_builtin_parser(t_node **token_tab);
void		free_tokens(t_node **token_tab);
void		executions(t_big *datas);
void		tree(t_node **tokens, t_big *datas);
void		*print_errors(char *error);

//LEXER
t_node		**ft_create_nodes(char *input, int nb);
int			ft_count_tokens(char *input);
int			ft_is_grammar(char *str, int i);

//TREE
void	exec_built_in(char *command, char **argv, t_big *datas);
void	exec_binary(char *command, char **argv);
void	print_std(int fd);

//GRAMMAR
void	exec_piped_cmd(char *command, char **argv, int is_built_in, t_big *datas);
void	exec_semicolon_cmd(char *command, char **argv, int is_built_in, t_big *datas);

//BUILTINS
int			ft_echo(char **arg, t_big *datas);
int			ft_cd(char **arg, t_big *datas);
int			ft_unset(char **arg, t_big *datas);
int			ft_pwd(t_big *datas);
int			ft_export(char **arg, t_big *datas);
int			ft_exit(t_big *datas, t_node *builtin);
char		*get_env(t_big *data, char *var);

int			cmp_list(t_var *lst, t_var *lst2);
t_var		*fill_tmp(char *str);

#endif
