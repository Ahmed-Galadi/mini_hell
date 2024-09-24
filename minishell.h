/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 04:34:17 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/02 03:19:27 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#define YELLOW "\001\033[93m\002"
#define RESET "\001\033[0m\002"
#define BOLD "\001\033[1m\002"
#define ORANGE "\001\033[38;5;214m\002"
#define GREEN_FG "\001\033[92m\002"
#define RED "\001\033[31m\002"
#define F_COLOR "\001\033[96m\002"
#define PINK "\001\033[38;5;13m\002"

#define PROMPT_MSG_1 F_COLOR " " RESET YELLOW " ┄─━࿅༻  " RESET ORANGE BOLD 
#define PROMPT_MSG_2 RESET YELLOW "༺  ࿅━─┄\n" RESET
#define VALID_ARROW GREEN_FG "❱ " RESET
#define UNVALID_ARROW RED "❱ " RESET


# define MAX_FDS 1024

typedef enum e_tokenType
{
	RED_IN,
	RED_IN_EXP,
	RED_OUT,
	RED_OUT_EXP,
	APPEND,
	APPEND_EXP,
	HERE_DOC,
	HERE_DOC_EXP,
	EXPAND,
	COMMAND,
	PIPE
}	e_tokenType;

typedef struct		s_token
{
	e_tokenType		type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct		s_opp
{
	e_tokenType		operator;
	char			*arg;
	struct s_opp	*next;
}					t_opp;

typedef struct		s_com
{
	char			**command;
	t_opp			*operator;
	struct s_com	*next;
}					t_com;

// execution types - start
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data {
	t_com	*command;
	t_env	*env;
	t_env	*export;
	char	*pwd;
	int		exit_status;
}	t_data;
// execution types - end

// execution prototypes
int		ft_echo(char **args, int *ret_val);
int		ft_env(t_env *env);
t_env	*init_env(char **env);
int		init_data(t_data *data, char **envp);
void	ft_printf_envs(t_env *env);
t_env   *convert_env_to_list(char **envp);
t_env   *create_env_node(char *env_str);
int		ft_cd(char **args, t_data *data, int *ret_val);
int		ft_unset(char **args, t_data *data, int *ret_val);
int		ft_pwd(t_data *data);
void	ft_exit(char **args, int *ret_val);
int		ft_export(char **args, t_data *data);
int		ft_export_command(t_env **my_env, const char *key, const char *value);
int		ft_execute_builtin(char **args, int *return_value, t_data *data, t_com *command);
int		ft_execute_command(t_com *command, int *return_value, t_data *data);
int		ft_execute_external(char **args, int *return_value, t_data *data, t_com *command);
char	*find_command(char *cmd, char **p_env);
char	**env_to_array(t_env *env);
// pipes prototypes
int		count_pipes(t_com *command);
char	***split_commands(t_com *commands, int num_commands);
void    free_commands(char ***commands, int num_commands);
int		ft_execute_pipeline(char ***commands, int num_commands, int *return_value, t_data *data);
// redirections
void	handle_redirections(t_com *command);
void	setup_input_redirection(const char *infile, int is_here_doc);
void	setup_output_redirection(const char *outfile, int is_appended);
void	restore_stdout(int stdout_copy);

// LIBFT Prototypes
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
// int		init_data(t_data *data, char **envp);
char	**env_to_array(t_env *env);

// utils
int		cstm_strcmp(char *str1, char *str2);
char	**ft_split(char const *s, char c);
void	ft_putstr(char *str);
void	add_lstback(t_opp *operators, t_opp *to_add);
t_token	*last_token(t_token *token);
char	**cstm_split(const char *str, const char *delims);
char *ft_itoa(int n);
// tokenizer
int		is_quote(char *str);
int		is_rederection(char *str);
char	*add_spaces(char *str);
void	switch_char(char **str, char to_find, char character);
char	*format(char *str);
char	*handle_quotes(char *str);
t_token	*tokenizer(char *input, t_env *env);
// expand
int		ft_isspace(char c);
void	expand_str(t_token **token, t_env *env, int exit_status);
// lexer
void	trim_quotes(t_token **token);
int		check_pipes(t_token *token);
int		check_red(t_token *token);
int		is_red(e_tokenType type);
e_tokenType red_type(t_token *token);
t_opp	*new_op(t_token **token);
t_com	*new_com(t_token *token);
bool	check_quote_syntax(char *input);
t_com	*create_cmds(t_token *token);
void	print_command(t_com *command);
void	print_opp(t_opp *opera);
void	print_token(t_token *token);
// errors
void	error(void);
int	syntax_error(t_token *token);
void	rl_replace_line(char *s, int a);
void execute_command(t_data *data, char **commands);
const char *get_path(const char *cmd, t_env *env);


#endif
