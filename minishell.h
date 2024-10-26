/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:40:40 by agaladi           #+#    #+#             */
/*   Updated: 2024/10/26 14:42:13 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>

# define YELLOW "\001\033[93m\002"
# define RESET "\001\033[0m\002"
# define BOLD "\001\033[1m\002"
# define ORANGE "\001\033[38;5;214m\002"
# define GREEN_FG "\001\033[92m\002"
# define RED "\001\033[31m\002"
# define F_COLOR "\001\033[96m\002"
# define PINK "\001\033[38;5;13m\002"

# define PROMPT_MSG_1 F_COLOR " " RESET YELLOW " ┄─━࿅༻  " RESET ORANGE BOLD 
# define PROMPT_MSG_2 RESET YELLOW "༺  ࿅━─┄\n" RESET
# define VALID_ARROW GREEN_FG "❱ " RESET
# define UNVALID_ARROW RED "❱ " RESET
# define CD_ERROR  "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n"

# define MAX_FDS 1024

# define PERM 126
# define ERROR 1
# define NOENT 127

typedef enum e_tokenType
{
	RED_IN,			// 0
	RED_OUT,		// 1
	APPEND,			// 2
	HERE_DOC_EXP,	// 3
	HERE_DOC,		// 4
	EXPAND,			// 5
	COMMAND,		// 6
	PIPE			// 7
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

typedef struct s_pipe
{
	int	*curr_pipe;
	int	*prev_pipe;
	int	num_commands;
	int	curr_command;
}					t_pipe;
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
	char	*last_exec_cmd;
}	t_shell;
// execution types - end

typedef struct s_expand_data
{
    char **token_val;
    t_env *env;
    int exit_status;
    int j; // Output index
    bool in_double_q; // Double quote state
    bool in_single_q; // Single quote state
} t_expand_data;

//garbage collector

typedef enum s_type
{
	LOCAL,
	GLOBAL
}			t_type;

typedef struct s_node
{
        void                    *ptr;
        struct s_node   *next;
}                               t_node;

typedef struct s_memory_list
{
        t_node  *head;
        t_node  *tail;
}                       t_memory_list;
void	add_memory(void *ptr, t_type type);
void	*gc_malloc(size_t size, t_type type);
void	gc_free_all(t_type type);


// execution prototypes
int		set_exit_status(int *status);
int		ft_echo(char **args, t_shell *data);
int		ft_env(t_env *env);
char	*ft_get_var_value(t_env *env ,const char *key);
t_env	*init_env(char **env, char *env_type);
int		init_shell_data_config(t_shell *data, char **envp);
void	ft_printf_envs(t_env *env);
t_env   *convert_env_to_list(char **envp, char *env_type);
t_env   *create_env_node(char *env_str);
int		ft_cd(char **args, t_shell *data);
int		ft_unset(char **args, t_shell *data);
int		ft_pwd(t_shell *data);
int		ft_exit(char **args, int exit_status);
int		ft_export(char **args, t_shell *data);
int		ft_export_command(t_env **my_env, const char *key, const char *value);
int		ft_execute_builtin(t_shell *data);
int		ft_execute_command(t_shell *data);
int		ft_execute_external(char **args, t_shell *data, t_com *command);
char	*find_command(char *cmd, char **p_env);
char	**env_to_array(t_env *env);
int		is_builtin(const char *cmd);
void	ft_get_vars(t_env *exp);
int		ft_set_vars(t_env **my_export_env, const char *key, const char *value);
char	*extract_key(char *str);
char	*extract_value(char *str);
int		is_var_exist(char *var, t_env *expo);
int		ft_check_key(const char *arg);
char	*ft_get_var_value(t_env *env, const char *key);
char    *get_operation(char *arg);

// pipes prototypes
int		count_pipes(t_com *command);
char	***split_commands(t_com *commands, int num_commands);
void    free_commands(char ***commands, int num_commands);
int		ft_execute_pipeline(char ***commands, int num_commands, t_shell *data);
void	update_prev_pipe(int *prev_pipe, int *curr_pipe, int is_not_last);
void	ft_init_pipe(t_pipe **pipe, int num_commands);
// redirections
int		handle_redirections(t_shell *data);
int		setup_input_redirection(const char *infile, int is_here_doc, t_shell *data);
int		setup_output_redirection(const char *outfile, int is_appended, t_shell *data);
void	restore_stdout(int stdout_copy);
void	redirect_to_pipe_fds(t_shell *data, int is_builtin, t_pipe *pipe);
int		is_redirection_in(e_tokenType operator);
int		is_redirection_out(e_tokenType operator);
int		valid_operator(e_tokenType operator_type, int *flags, int *default_fd);
void    close_all_fds(int *fds, int count);
void    handle_files_redirections(t_opp *curr_op, t_shell *data);
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
char	*ft_strjoin(char const *s1, char const *s2, t_type type);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_isalnum(int c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, int n);
int		first_occurence(char *str, char c);
// int		init_shell_data_config(t_shell *data, char **envp);
char	**env_to_array(t_env *env);

// utils
int		cstm_strcmp(char *str1, char *str2);
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
void	expand(char **token_val, t_env *env, int *exit_status);
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
