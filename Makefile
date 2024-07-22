# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 23:26:11 by agaladi           #+#    #+#              #
#    Updated: 2024/07/22 10:39:32 by agaladi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
SRCS = parsing/errors/error_handler.c  parsing/formater/add_spaces.c \
parsing/formater/formater.c  parsing/tokenizer/token_check.c \
parsing/tokenizer/tokenizer.c \
utils/str_utils.c utils/ft_split.c utils/list_utils.c main.c
CFLAGS = -Wall -Wextra -Werror
DEPS = main.h
LIB = main.a
OUT = minishell
OBJS = $(SRCS:.c=.o)

all: $(OUT)

$(OUT): $(OBJS) $(DEPS)
	$(CC) $(CFLAGS) -lreadline $(OBJS) -o $(OUT)

$(LIB): $(OBJS)
	ar -rc $(LIB) $(OBJS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(LIB)

fclean: clean
	rm -rf $(OUT)

re: fclean all

recom: all
	rm -rf $(OBJS) $(LIB)
