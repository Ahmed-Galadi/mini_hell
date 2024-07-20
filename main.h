/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 04:34:17 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/18 15:26:54 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>


typedef enum e_tokenType
{
	red_in,
	red_out,
	append_out,
	here_doc,
}	e_tokenType;

typedef struct	s_opperator
{
	e_tokenType	type;
	char		*file;
	char		*delimiter;
	struct s_opperator *next;
} 				t_opperator;

typedef struct	s_command
{
	char		*command;
	char		**flag;
	t_opperator	*operator;
	char		**options;
}				t_command;

typedef struct s_exec
{
	struct s_exec *prev;
	t_command		*command;
	struct s_exec	*next;
}	t_exec;

// utils
int			ft_strlen(char *str);
int			ft_strcmp(char *str1, char *str2);
char		**ft_split(char const *s, char c);
void		add_lstback(t_opperator *operators, t_opperator *to_add);
// tokenizer
int			is_quote(char *str);
int			is_rederection(char *str);
int			is_command(char *str);
int			is_flag(char *str);
char		*trim_quotes(char *str);
char		*add_spaces(char *str);
void		switch_char(char *str, char to_find, char character);
char		*format(char *str);
// errors
void	error(void);

#endif