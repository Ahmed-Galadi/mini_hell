# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 23:26:11 by agaladi           #+#    #+#              #
#    Updated: 2024/10/07 14:39:20 by bzinedda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
USER := $(shell whoami)
LIBFT_SRCS = libft/ft_strchr.c libft/ft_strlen.c libft/ft_split.c \
		     libft/ft_strjoin.c libft/ft_strncmp.c libft/ft_strcmp.c \
			 libft/ft_strdup.c libft/ft_atoi.c libft/ft_substr.c \
			 libft/find_executable.c libft/ft_isalnum.c libft/ft_strcpy.c libft/ft_strncpy.c\

EXECUTION_SRCS = execution/builtings/ft_echo.c execution/builtings/ft_env.c \
				 execution/builtings/ft_pwd.c execution/builtings/ft_export.c \
				 execution/builtings/ft_init_data.c execution/builtings/ft_exit.c \
				 execution/builtings/ft_unset.c execution/builtings/ft_cd.c  \
				 execution/builtings/builtings_utils/utils.c \
				 execution/execution_types/execute_external.c \
				 execution/execution_types/execute_command.c \
				 execution/execution_types/execute_builtin.c \
				 execution/pipes/pipe_utils.c execution/pipes/pipeline.c \
				 execution/redirections/redirection_types.c \
				 execution/redirections/redirection_utils.c \
				 execution/redirections/heredoc_utils.c \

PARSING_SRCS = parsing/errors/error_handler.c  parsing/formater/add_spaces.c \
parsing/expand/expand_utils.c parsing/expand/expand.c parsing/formater/formater.c parsing/formater/quotes_handler.c \
parsing/tokenizer/token_check.c parsing/tokenizer/tokenizer.c \
parsing/lexer/lexing_checks.c parsing/lexer/lexer.c parsing/lexer/syntax_errors.c \
utils/str_utils.c utils/cstm_split.c utils/list_utils.c utils/itoa.c utils/garbage_collector.c main.c\

CFLAGS = -g
CFLAGS_R = -g -lreadline
HEADER = minishell.h
LIB = minishell.a
NAME = minishell

PARSING_OBJS =  $(addprefix obj/, $(PARSING_SRCS:.c=.o))
EXECUTION_OBJS = $(addprefix obj/, $(EXECUTION_SRCS:.c=.o))
LIBFT_OBJS = $(addprefix obj/, $(LIBFT_SRCS:.c=.o))

ifeq ($(USER), agaladi)
	CFLAGS_R += -L/Users/agaladi/.brew/opt/readline/lib
else
	CFLAGS_R += -L/Users/bzinedda/.brew/opt/readline/lib
endif

all: $(NAME)

$(NAME): $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(CFLAGS_R) $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS) -o $@

$(LIB): $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS)
	ar -rc $(LIB) $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS)

obj/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj $(LIB)

fclean: clean
	rm -rf $(NAME)

re: fclean all
