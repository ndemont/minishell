/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 15:29:44 by ndemont           #+#    #+#             */
/*   Updated: 2021/05/21 23:41:26 by ndemont          ###   ########.fr       */
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

//MACRO ERRORS
# define ERROR 0
# define SUCCESS 1
# define BUILT_IN_FAILURE -1
# define BREAK_LOOP 2

typedef struct s_global
{
	struct termios		term;
	struct termios		save;
	int					enter;
	int					c_max;
	int					l_max;
	int					c_pos;
	int					l_pos;
	int					c_start;
	int					line_lvl;
	int					child;
	int					signal;
	int					ret;
	int					exit;
	int					cursor_max;
	int					cursor_lvl;
	int					cursor_pos;
	char				*current_dir;
}	t_global;

typedef struct s_node
{
	int					type;
	char				*input;
	char				**arg;
	char				*builtin;
	char				*command;
	struct s_node		*left;
	struct s_node		*right;
}	t_node;

typedef struct s_var
{
	char	*var;
	char	*value;
}	t_var;

typedef struct s_history
{
	int					status;
	char				*command;
	struct s_history	*prev;
	struct s_history	*next;
}	t_history;

typedef struct s_big
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
	char				*browse;
	char				*input;
}	t_big;

//DECLARE OF A GLOBAL STRUCT, MANDATORY FOR TERMCAPS MANAGMENT 
t_global				g_tcaps;

//ENV
int						ft_env(char **av, t_big *datas);
int						store_env(char **env, t_big *datas);
int						ft_hidden(char **argv, t_big *datas);
int						check_duplicate(t_list *list, char *ref);
int						actualize_list(char *line, t_list *lst);
char					**ft_split_on_equal(char *str);
int						add_to_list(char *line, t_list **lst);
void					actualize_return_status(int ret_status);
char					**get_arguments(t_node *root, t_big *datas);
char					**replace_variable(t_node *root, t_big *datas);
int						check_arg_conformity(char *line);
t_list					**store_first_elem(char *env_elem);
int						store_others_elem(char *env_elem, t_list **start);
t_var					*fill_tmp(char *str);
int						cd_actualize_env(t_list **lst);
int						add_hidden_to_env_export(char *line, t_big *datas);
int						actualize_export_add_env(char *line, t_big *datas);
int						actualize_export_actualize_env(char *line, \
t_big *datas);
int						add_hidden_add_export_add_env(char *line, t_big *datas);
int						add_hidden_add_export(char *line, t_big *datas);
char					*get_identifier(char *str);
int						check_duplicate(t_list *list, char *ref);
int						check_plus_conformity(char *line);
int						check_arg_conformity(char *line);
void					print_export(t_list **list);
int						treat_list(char *arg, t_big *datas);
char					**build_array(char *command, t_list *env);
void					close_pipes(int *fd);
void					pipe_magic(int fd[2], t_big *datas);
int						create_pipe_do_fork(int fd[2], pid_t *pid1, \
int *ret_status);
int						check_isspace(char *input);

//HISTORY
int						init_history(t_big *datas);
void					save_history(char *line, t_big *datas);
int						browse_history(t_big *datas, char **line, int signal);
t_history				*browse_up(t_history *current, char **browse, \
t_big *datas, char *input);
t_history				*browse_down(t_history *current, char **browse, \
t_big *datas, char *input);
int						update_history_list(t_history **begin, char *line, \
int status);
int						cmp_history(char **browse, t_history *tmp);
int						update_history_file(t_big *datas);

//PROMPT
int						display_prompt(void);
int						display_directory(void);

//FREE
int						free_datas(t_big *datas);
void					free_tokens(t_node **token_tab);
void					free_tree(t_node *root);
void					free_list(t_list **list);
void					free_history(t_history **list);
void					free_arg(char **arg);
void					clean_datas(t_big *datas);
void					free_elems_print_error(char **str, t_var **tmp);

//ERRORS
char					**printcc_stderr(char *cmd, char *strerror, int exit);
char					*printc_stderr(char *cmd, char *strerror, int exit);
int						printi_stderr(char *cmd, char *strerror, int exit);

//AST
int						read_input(t_big *datas);
t_node					**ft_lexer(char *input);
t_node					**ft_parser(t_node **token_tab);
void					executions(t_big *datas);
int						tree(t_node **tokens, t_big *datas);
void					*print_errors(char *error, int exit);
int						print_errors_int(char *error, int exit);
void					semicolon_node(t_node **tokens, t_big *datas, int i);
void					right_redir_node(t_node **tokens, t_big *datas, int i, \
t_node *prev);
void					left_redir_node(t_node **tokens, t_big *datas, int i, \
t_node *prev);
void					pipe_node(t_node **tokens, t_big *datas, int i);

//LEXER
t_node					**ft_create_nodes(char *input, int nb);
int						count_arg(char *input);
char					*get_double_quote(char *input, int *i, int j);
char					*get_single_quote(char *input, int *i, int *j);
char					*get_backslash(char *input, int *i, int j);
char					*get_arg(char *input, int *i);
char					*get_variable_part(char **new, char *input, int *i);
char					*get_variable_str(char *input, int *i, int end, int j);
int						ft_count_tokens(char *input);
int						gram(char *str, int i, int *isspace);
char					*get_variable(char *input, int *k);
char					*get_variable_quotes(char *str, int *k);
t_node					*ft_init_grammar_node(int type);
t_node					*ft_init_buildin_node(char *input, int type);
char					*get_tilde(int *i);
char					*get_first_quote(char **new, char *input, int *i, int start);

//TREE
int						exec_built_in(char *command, char **argv, t_big *datas);
int						exec_binary(char *command, char **argv, t_big *datas);
void					print_std(int fd);
void					no_parent(t_node *root, int n, t_big *datas, int side);
void					pipe_parent(t_node *root, int n, t_big *datas, \
int side);
void					semicolon_parent(t_node *root, int n, t_big *datas, \
int side);
void					right_redir_parent(t_node *root, int n, t_big *datas, \
int side);
void					left_redir_parent(t_node *root, int n, t_big *datas, \
int side);

//GRAMMAR
void					exec_piped_cmd(char *cmd, char *builtin, char **av, \
t_big *datas);
void					exec_semicolon_cmd(char *command, char **argv, \
int is_built_in, t_big *datas);
void					redirections(int type, char **argv, t_big *datas);
int						exec_anglebracket_right(char **argv, t_big *datas);
void					print_std_fd(int fd_in, int fd_out);
int						ft_copy_arg(char **argv, t_big *datas);
int						check_ambiguous_arg(char **argv, t_big *datas);

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
int						shell_lvl(t_big *datas);
int						increment_shell_lvl(char **level, t_list *tmp);
void					clean_if_mallocked(char **level, char **var, \
char **value);
char					*get_env_var(char *str, int *i, t_big *datas);

//TERMCAPS
int						term_size(void);
int						termcaps_init(void);
int						raw_mode(void);
int						normal_mode(void);
int						cursor_position(void);
int						do_the_right_thing(int *i, char *buf, char **line, \
t_big *datas);
int						ft_putchar2(int c);
int						print_at_cursor(char c);
int						ctrl_d(t_big *datas, char **line, int *i);
void					lines_added(char *str);
int						move_cursor(int c, int l);
int						scroll_n_times(int n);
int						clear_term(void);
int						clear_after_cursor(void);
int						move_cursor_left(void);
int						move_cursor_right(void);
int						add_at_cursor(char c, int *i, char **line);
int						backspace(int *i, char **line);
int						backspace_at_cursor(int *i, char **line);
int						get_cursor_max(void);
int						move_cursor_up(void);
int						move_cursor_down(void);
int						word_left(char **line);
int						word_right(int *i, char **line);
void					actualize_cursor(int new_c_pos, int new_l_pos);
void					clean_the_mess(char **tmp, char **oldline, char **line);

//FLAGS
void					ft_signals(int sig);

//LINE_CREATION
char					*create_line(t_big *datas);
void					check_if_non_print(char *buf, int *non_print_flag, \
t_big *datas);
int						launch_termcaps(char *buf, char **line, int *i, \
t_big *datas);
int						edit_and_print_line(char *buf, char **line, int *i);

#endif
