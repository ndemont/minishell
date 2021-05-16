# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpetit <gpetit@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/19 16:49:20 by gpetit            #+#    #+#              #
#    Updated: 2021/05/16 12:34:41 by gpetit           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = clang

CFLAGS = -Wall -Werror -Wextra

SRCS = ft_calloc.c ft_isascii.c ft_itoa.c ft_memmove.c ft_putendl_fd.c ft_split.c \
	ft_strjoin.c ft_strlen.c ft_dbstrlen.c ft_strnstr.c ft_substr.c ft_atoi.c ft_isalnum.c \
	ft_isdigit.c ft_memccpy.c ft_memchr.c ft_memset.c ft_memcmp.c ft_putnbr_fd.c ft_strchr.c ft_strlcat.c \
	ft_strmapi.c ft_strrchr.c ft_tolower.c ft_bzero.c ft_isalpha.c ft_isprint.c \
	ft_memcpy.c ft_putchar_fd.c ft_putstr_fd.c ft_strdup.c ft_strlcpy.c ft_strcmp.c ft_strncmp.c \
	ft_strtrim.c ft_toupper.c ft_splits.c get_next_line.c ft_lstadd_back.c ft_lstadd_front.c \
	ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
	ft_lstlast.c ft_lstnew.c ft_lstsize.c ft_lstmap.c ft_putstr.c ft_putchar.c free_double.c ft_lst_sort.c \
	ft_realloc.c ft_putendl.c ft_putnbr.c ft_print_hexa.c ft_clean_free.c


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY : all clean fclean bonus re
