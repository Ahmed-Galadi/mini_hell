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

# define BASH_PROMPT_NAME "big-bash-0.1 "
// execution types - start
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data {
	t_env	*env;
	t_env	*export;
	char	*pwd;
}	t_data;

// execution types - end
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
	S_QUOTE,
	D_QUOTE,
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
int		ft_execute_builtin(char **args, int *return_value, t_data *data);
int		ft_execute_command(char **args, int *return_value, t_data *data);
int		ft_execute_external(char **args, int *return_value, t_data *data);
char	*find_command(char *cmd, char **p_env);
char	**env_to_array(t_env *env);
// pipes prototypes
int		count_pipes(char **args);
char	***split_commands(char **args, int num_commands);
int		count_args_until_pipe(char **args);
void    free_commands(char ***commands, int num_commands);
int		ft_execute_pipeline(char ***commands, int num_commands, int *return_value, t_data *data);

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
int		init_data(t_data *data, char **envp);
char	**env_to_array(t_env *env);

// utils
char	**ft_split(char const *s, char c);
void	ft_putstr(char *str);
void	add_lstback(t_opp *operators, t_opp *to_add);
t_token	*last_token(t_token *token);
// tokenizer
int		is_quote(char *str);
int		is_rederection(char *str);
char	*add_spaces(char *str);
void	switch_char(char **str, char to_find, char character);
char	*format(char *str);
char	*handle_quotes(char *str);
t_token	*tokenizer(char *input);
// lexer
void	trim_quotes(t_token **token);
int		check_pipes(t_token *token);
int		check_red(t_token *token);
int		is_red(e_tokenType type);
void	set_expand(t_token **token);
e_tokenType red_type(t_token *token);
t_opp	*new_op(t_token **token);
// errors
void	error(void);

#endif