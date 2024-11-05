# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 23:26:11 by agaladi           #+#    #+#              #
#    Updated: 2024/11/04 22:22:15 by agaladi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc #-Wall -Wextra -Werror
USER := $(shell whoami)

LIBFT_SRCS = libft/ft_strchr.c libft/ft_strlen.c libft/ft_split.c \
		     libft/ft_strjoin.c libft/ft_strncmp.c libft/ft_strcmp.c \
			 libft/ft_strdup.c libft/ft_atoi.c libft/ft_substr.c \
			 libft/find_executable.c libft/ft_isalnum.c libft/ft_strcpy.c libft/ft_strncpy.c \
			 libft/first_occurence.c

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
				 execution/redirections/helper.c \
				 execution/builtings/builtings_utils/env_utils.c \
				 execution/builtings/builtings_utils/export_utils.c \
				 printf/ft_print_chr.c printf/ft_print_hex.c printf/ft_print_nbr.c printf/ft_print_percentage.c printf/ft_print_ptr.c printf/ft_print_str.c printf/ft_print_un_nbr.c printf/ft_printf.c printf/ft_ptr_len.c printf/ft_putchar.c printf/ft_putnbr.c printf/ft_putnbr_base.c printf/ft_putstr.c printf/ft_space.c
				 
PARSING_SRCS = parsing/errors/error_handler.c  parsing/formater/add_spaces.c \
parsing/expand/expand_utils.c parsing/expand/expand_loop.c parsing/expand/expand_loop_utils.c parsing/expand/expand.c parsing/formater/formater.c parsing/formater/quotes_handler.c \
parsing/tokenizer/token_check.c parsing/tokenizer/tokenizer.c \
parsing/lexer/lexing_checks.c parsing/lexer/lexer.c parsing/lexer/syntax_errors.c \
utils/str_utils.c utils/cstm_split.c utils/list_utils.c utils/itoa.c utils/garbage_collector.c main.c prompt.c \
utils/shell_utils.c utils/signals_utils.c

CFLAGS = -g #-fsanitize=address
CFLAGS_R = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -lhistory
HEADER = minishell.h
LIB = minishell.a
NAME = minishell

PARSING_OBJS =  $(addprefix obj/, $(PARSING_SRCS:.c=.o))
EXECUTION_OBJS = $(addprefix obj/, $(EXECUTION_SRCS:.c=.o))
LIBFT_OBJS = $(addprefix obj/, $(LIBFT_SRCS:.c=.o))

all: $(NAME)

$(NAME): $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(CFLAGS_R) $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS) -o $@

$(LIB): $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS)
	ar -rc $(LIB) $(PARSING_OBJS) $(EXECUTION_OBJS) $(LIBFT_OBJS)

obj/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -I/Users/$(USER)/.brew/opt/readline/include $< -o $@

clean:
	rm -rf obj $(LIB)

fclean: clean
	rm -rf $(NAME)

re: fclean all
