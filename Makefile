# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 23:26:11 by agaladi           #+#    #+#              #
#    Updated: 2024/08/26 17:37:16 by bzinedda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -g
LIBFT_SRCS = libft/ft_strchr.c libft/ft_strlen.c libft/ft_split.c \
		     libft/ft_strjoin.c libft/ft_strncmp.c libft/ft_strcmp.c \
			 libft/ft_strdup.c libft/ft_atoi.c libft/ft_substr.c \
			 libft/find_executable.c

EXECUTION_SRCS = execution/builtings/ft_echo.c execution/builtings/ft_env.c \
				 execution/builtings/ft_pwd.c execution/builtings/ft_export.c \
				 execution/builtings/ft_init_data.c execution/builtings/ft_exit.c \
				 execution/builtings/ft_unset.c execution/builtings/ft_cd.c  \
				 execution/builtings/builtings_utils/utils.c \
				 execution/execution_types/execute_external.c \
				 execution/execution_types/execute_command.c \
				 execution/execution_types/execute_builtin.c \
				 execution/pipes/pipe_utils.c execution/pipes/pipeline.c \

PARSING_SRCS = parsing/errors/error_handler.c  parsing/formater/add_spaces.c \
parsing/formater/formater.c parsing/formater/quotes_handler.c \
parsing/tokenizer/token_check.c parsing/tokenizer/tokenizer.c \
parsing/lexer/lexing_checks.c parsing/lexer/lexer.c \
utils/str_utils.c utils/list_utils.c main.c

CFLAGS = -Wall -Wextra -Werror
HEADER = minishell.h
LIB = main.a
OUT = minishell
PARSING_OBJS = $(PARSING_SRCS:.c=.o)
EXECUTION_OBJS = $(EXECUTION_SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

all: $(OUT)

$(OUT): $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS) $(HEADER)
	$(CC) $(CFLAGS) -lreadline $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS) -o $(OUT)

$(LIB): $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS)
	ar -rc $(LIB) $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS) $(LIB)

fclean: clean
	rm -rf $(OUT)

re: fclean all

recom: all
	rm -rf $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS) $(LIB)
