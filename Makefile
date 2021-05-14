# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/22 14:42:49 by gpetit            #+#    #+#              #
#    Updated: 2021/05/14 18:01:48 by ndemont          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

IFLAGS = -I${INC_DIR}

LIBFT = -Llibft -lft -ltermcap

SRCS = $(addprefix srcs/, main.c display_prompt.c lexer/lexer.c lexer/parser.c lexer/count.c lexer/initialisation.c\
	lexer/nodes.c lexer/tokens.c lexer/variables.c lexer/odd_chars.c free/free.c ast/binaries.c ast/tree.c ast/branches.c\
	lexer/arguments.c errors/errors.c builtins/echo.c builtins/cd.c builtins/env.c builtins/pwd.c \
	builtins/exit.c builtins/export.c builtins/unset.c builtins/hidden.c grammar/pipe.c \
	grammar/semicolon.c grammar/redirection.c history/init_history.c variables/variable.c \
	history/update_history.c history/browse_history.c history/save_history.c variables/arguments.c\
	DEVELOPMENT_MODE.c signals/signals.c termcaps/ctrl_d.c termcaps/termcaps.c \
	termcaps/termcaps_utils.c termcaps/termcaps_scroll.c termcaps/termcaps_cursor.c \
	termcaps/termcaps_backspace.c termcaps/termcaps_add_char.c termcaps/termcaps_cursor_moves.c termcaps/termcaps_words_move.c)

INC_DIR = includes

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

clean:
	make clean -C libft/
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

cleandb:
	rm -f DEBUG_str DEBUG_sequence DEBUG_termcaps

re: fclean $(NAME)
