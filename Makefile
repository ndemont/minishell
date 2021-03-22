# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpetit <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/22 14:42:49 by gpetit            #+#    #+#              #
#    Updated: 2021/03/22 17:40:09 by gpetit           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I${INC_DIR}

LIBFT = -Llibft -lft

SRCS = $(addprefix srcs/, main.c display_prompt.c)

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
