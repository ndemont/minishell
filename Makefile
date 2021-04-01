# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/22 14:42:49 by gpetit            #+#    #+#              #
<<<<<<< Updated upstream
#    Updated: 2021/04/01 13:20:08 by ndemont          ###   ########.fr        #
=======
#    Updated: 2021/04/01 17:24:46 by gpetit           ###   ########.fr        #
>>>>>>> Stashed changes
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -g3

IFLAGS = -I${INC_DIR}

LIBFT = -Llibft -lft

<<<<<<< Updated upstream
SRCS = $(addprefix srcs/, main.c display_prompt.c lexer.c buildin_parser.c free.c)
=======
SRCS = $(addprefix srcs/, main.c display_prompt.c lexer.c buildin_parser.c binaries.c)
>>>>>>> Stashed changes

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

re: fclean $(NAME)
