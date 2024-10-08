/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:40:40 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/28 20:40:51 by agaladi          ###   ########.fr       */
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
# include <termios.h>

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
	RED_OUT,
	APPEND,
	HERE_DOC_EXP,
	HERE_DOC,
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
	char	**heredoc_files;
	int		exit_status;
	int		heredoc_count;
	int		heredoc_index;
}	t_shell;
// execution types - end

typedef struct	s_expand_data
{
    char	**token_val;
    t_env	*env;
    int		exit_status;
}			t_expand_data;

// execution prototypes
int		ft_echo(char **args);
int		ft_env(t_env *env);
t_env	*init_env(char **env, char *env_type);
int		init_shell_data_config(t_shell *data, char **envp);
void	ft_printf_envs(t_env *env);
t_env   *convert_env_to_list(char **envp, char *env_type);
t_env   *create_env_node(char *env_str);
int		ft_cd(char **args, t_shell *data);
int		ft_unset(char **args, t_shell *data);
int		ft_pwd(t_shell *data);
int	ft_exit(char **args, int exit_status);
int		ft_export(char **args, t_shell *data);
int		ft_export_command(t_env **my_env, const char *key, const char *value);
int		ft_execute_builtin(t_shell *data);
int		ft_execute_command(t_shell *data);
int		ft_execute_external(char **args, t_shell *data, t_com *command);
char	*find_command(char *cmd, char **p_env);
char	**env_to_array(t_env *env);
int		is_builtin(const char *cmd);
// pipes prototypes
int		count_pipes(t_com *command);
char	***split_commands(t_com *commands, int num_commands);
void    free_commands(char ***commands, int num_commands);
int		ft_execute_pipeline(char ***commands, int num_commands, t_shell *data);
// redirections
void	handle_redirections(t_shell *data);
void	setup_input_redirection(const char *infile, int is_here_doc, t_shell *data);
void	setup_output_redirection(const char *outfile, int is_appended);
void	restore_stdout(int stdout_copy);
void	redirect_to_pipe_fds(t_shell *data, int *prev_pipe,
			int *curr_pipe, int curr_cmd, int num_commands, int is_builtin);
void    close_all_fds(int *fds, int count);
void    handle_files_redirections(t_opp *curr_op);
int		heredoc_count(t_com *command);
char	**fill_heredoc_files(int count);
void	ftputstr_fd(int fd, char *s);
void	open_heredoc(char **files, t_opp *op, int *count, t_shell *data);
void	ft_open_heredoc(t_shell *data);
int		ft_read_from_heredoc(t_shell *data);

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
int		ft_isalnum(int c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, int n);
// int		init_shell_data_config(t_shell *data, char **envp);
char	**env_to_array(t_env *env);

// utils
int		cstm_strcmp(char *str1, char *str2);
char	**ft_split(char const *s, char c);
void	ft_putstr(char *str);
void	add_lstback(t_opp *operators, t_opp *to_add);
t_token	*last_token(t_token *token);
char	**cstm_split(const char *str, const char *delims);
char *ft_itoa(int n);
int	is_op(char c);
// tokenizer
int		is_quote(char *str);
int		is_rederection(char *str);
char	*add_spaces(char *str);
void	switch_char(char **str, char to_find, char character);
char	*format(char *str);
char	*format_and_switch(char *input);
t_token	*tokenizer(char *input, t_env *env, int *exit_status);
void	heredoc_type_set(t_token **token);
bool	has_quotes(char *str);
// expand
void	expand(char **token_val, t_env *env, int exit_status);
int		ft_isspace(char c);
char	*get_expand_val(char *str, t_env *env, int *i, int exit_status);
void	handle_quotes_state(char c, bool *in_single_q, bool *in_double_q);
int		calculate_size(char *str, t_env *env, int exit_status);
void	expand_str(t_token **token, t_env *env, int exit_status);
// lexer
void	trim_quotes(t_token **token);
int		check_pipes(t_token *token);
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
void execute_command(t_shell *data, char **commands);
const char *get_path(const char *cmd, t_env *env);


#endif
