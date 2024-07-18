# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/18 15:08:26 by agaladi           #+#    #+#              #
#    Updated: 2024/07/18 15:08:59 by agaladi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
SRCS = main.c
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