/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:29:44 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/06 11:36:59 by ndemont          ###   ########.fr       */
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
	int					c_max;
	int					l_max;
	int					c_pos;
	int					l_pos;
	int 				c_start;
	int					line_lvl;
	int					child;
	int 				signal;
	int					ret;
	int					cursor_max;
	int					cursor_lvl;
	int					cursor_pos;
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
	int					fd_out;
	int					quit;
	int					flag_pipe;
	int					flag_bracket;
	int					flag_left_bracket;
	int					flag_history;
	char				*file_name;
	char				**redirection_arg;
	t_list				**env;
	t_list				**export;
	t_list				**hidden;
	t_history			**history;
	t_node				*root;
}						t_big;

//DECLARE OF A GLOBAL STRUCT, MANDATORY FOR TERMCAPS MANAGMENT 
t_caps					tcaps;

//ENV
int						ft_env(char **av, t_big *datas);
void					store_env(char **env, t_big *datas);
int						ft_hidden(char **argv, t_big *datas);
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
void					clean_datas(t_big *datas);

//AST
int						read_input(t_big *datas);
t_node					**ft_lexer(char *input);
t_node					**ft_builtin_parser(t_node **token_tab);
void					executions(t_big *datas);
void					tree(t_node **tokens, t_big *datas);
void					*print_errors(char *error);
void					semicolon_node(t_node **tokens, t_big *datas, int i);
void					right_redirection_node(t_node **tokens, t_big *datas, int i, t_node *prev);
void					left_redirection_node(t_node **tokens, t_big *datas, int i, t_node *prev);
void					pipe_node(t_node **tokens, t_big *datas, int i);

//LEXER
t_node					**ft_create_nodes(char *input, int nb);
int						count_arg(char *input);
char					*get_single_quote(char *input, int *i, int *j);
char					*get_arg(char *input, int *i);
int						ft_count_tokens(char *input);
int						ft_is_grammar(char *str, int i);

//TREE
int						exec_built_in(char *command, char **argv, t_big *datas);
void					exec_binary(char *command, char **argv);
void					print_std(int fd);

//GRAMMAR
void					exec_piped_cmd(char *cmd, char *builtin, char **av, t_big *datas);
void					exec_semicolon_cmd(char *command, char **argv, int is_built_in, t_big *datas);
void					redirections(int type, char **argv, t_big *datas);
void					exec_anglebracket_right(char **argv, t_big *datas);
void					print_std_fd(int fd_in, int fd_out);

//BUILTINS
int						ft_echo(char **arg, t_big *datas);
int						ft_cd(char **arg, t_big *datas);
int						ft_unset(char **arg, t_big *datas);
int						ft_pwd(t_big *datas);
int						ft_export(char **arg, t_big *datas);
int						ft_exit(char **arg, t_big *datas);
char					*get_env(t_big *data, char *var);

int						cmp_list(t_var *lst, t_var *lst2);
t_var					*fill_tmp(char *str);
void					init_data(t_big *datas);
void					actualize_data(t_big *datas);
int						display_prompt(void);


//TERMCAPS
void					term_size(void);
void					termcaps_init(void);
void					raw_mode(void);
void					normal_mode(void);
void					cursor_position(void);
void					do_the_right_thing(int *i, char *buf, char **line, t_big *datas);
int						ft_putchar2(int);
void					print_at_cursor(char c);
void					ctrl_d(t_big *datas, char **line, int *i);
void					lines_added(char *str);
void					move_cursor(int c, int l);
void					scroll_n_times(int n);
void					clear_term(void);
void					clear_after_cursor(void);
void					print_at_cursor(char c);
void					move_cursor_left(void);
void					move_cursor_right(void);
void 					add_at_cursor(char c, int *i, char **line);
void					backspace(int *i, char **line);
void					backspace_at_cursor(int *i, char **line);
void					get_cursor_max(void);
void					move_cursor_up(void);
void					move_cursor_down(void);
void					word_left(char **line);
void					word_right(int *i, char **line);


//FLAGS
void					ft_signals(int sig);


//DEVELOPPEMENT MODE
void					DEVELOPMENT_MODE_print_sequence(char *buf); //DELETE BEFORE PUSH
void					DEVELOPMENT_MODE_print_termcaps(char *str); //DELETE BEFORE PUSH
void					DEVELOPMENT_MODE_print_str(char *buf);
void					DEVELOPMENT_MODE_print_nbr(long n);


#endif
