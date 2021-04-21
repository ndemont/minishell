/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:29:44 by ndemont           #+#    #+#             */
/*   Updated: 2021/04/28 12:55:21 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define RET_ERROR 127

# define CLEAR "\e[H\e[2J"

typedef struct			s_caps
{
	struct termios		term;
	struct termios		save;
	int					l_prompt;
	int					c_max;
	int					l_max;
	int					c_pos;
	int					l_pos;
	int 				c_start;
	int					line_lvl;
	int					child;
	int					ret;
}						t_caps;

typedef struct			s_node
{
	int					type;
	char				*input;
	char				**arg;
	char				*ret;
	char				*builtin;
	char				*command;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

typedef struct			s_var
{
	char *var;
	char *value;
}						t_var;

typedef struct			s_history
{
	int					status;
	char				*command;
	struct s_history	*prev;
	struct s_history	*next;
}						t_history;

typedef struct			s_big
{
	int					fd;
	int					quit;
	int					flag_pipe;
	int					flag_bracket;
	int					flag_left_bracket;
	int					flag_history;
	char				*redirection_arg;
	t_list				**env;
	t_list				**export;
	t_list				**hidden;
	t_history			**history;
	t_node				*root;
}						t_big;

//DECLARE OF A GLOBAL STRUCT, MANDATORY FOR TERMCAPS MANAGMENT 
t_caps					tcaps;

//ENV
int						ft_env(t_big *datas);
void					store_env(char **env, t_big *datas);
void					ft_hidden(char **argv, t_big *datas);
int						check_duplicate(t_list *list, char *ref);
void					actualize_list(char *line, t_list *lst);
char 					**ft_split_on_equal(char *str);
void					add_to_list(char *line, t_list **lst);

//HISTORY
void					init_history(t_big *datas);
void					save_history(char *line, t_big *datas);
void					browse_history(t_big *datas, char **line, int signal);
void					update_history_list(t_history **begin, char *line, int status);
void					update_history_file(t_big *datas);

//FREE
void					free_datas(t_big *datas);
void					free_tokens(t_node **token_tab);

//AST
int						read_input(t_big *datas);
t_node					**ft_lexer(char *input);
t_node					**ft_builtin_parser(t_node **token_tab);
void					executions(t_big *datas);
void					tree(t_node **tokens, t_big *datas);
void					*print_errors(char *error);

//LEXER
t_node					**ft_create_nodes(char *input, int nb);
int						ft_count_tokens(char *input);
int						ft_is_grammar(char *str, int i);

//TREE
void					exec_built_in(char *command, char **argv, t_big *datas);
void					exec_binary(char *command, char **argv);
void					print_std(int fd);

//GRAMMAR
void					exec_piped_cmd(char *command, char **argv, int is_built_in, t_big *datas);
void					exec_semicolon_cmd(char *command, char **argv, int is_built_in, t_big *datas);
void					redirections(int type, char **argv, t_big *datas);
void					exec_anglebracket_right(char **argv, t_big *datas);

//BUILTINS
int						ft_echo(char **arg, t_big *datas);
int						ft_cd(char **arg, t_big *datas);
int						ft_unset(char **arg, t_big *datas);
int						ft_pwd(t_big *datas);
int						ft_export(char **arg, t_big *datas);
int						ft_exit(t_big *datas, t_node *builtin);
char					*get_env(t_big *data, char *var);

int						cmp_list(t_var *lst, t_var *lst2);
t_var					*fill_tmp(char *str);
void					init_data(t_big *datas);
void					actualize_data(t_big *datas);
int						display_prompt(void);


//TERMCAPS
void		      			term_size(void);
void					termcaps_init(void);
void					raw_mode(void);
void					normal_mode(void);
void					cursor_position(void);
void					do_the_right_thing(int *i, char *buf, char **line, t_big *datas);
int					ft_putchar2(int);
void					print_at_cursor(char c);
void					end_of_transmission(t_big *datas, char *line);

//FLAGS
void					ft_signals(int sig);


//DEVELOPPEMENT MODE
void					DEVELOPMENT_MODE_print_sequence(char *buf); //DELETE BEFORE PUSH
void					DEVELOPMENT_MODE_print_termcaps(void); //DELETE BEFORE PUSH
void					DEVELOPMENT_MODE_print_str(char *buf);

#endif
