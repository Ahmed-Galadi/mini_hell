/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/10/09 12:17:39 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	p_token(t_token *token)
{
	t_token	*current;

	if (!token)
	{
		printf("empty token!\n");
		return ;
	}
	current = token;
	while (current)
	{
		printf("Type: %d", current->type);
		if (current->value)
			printf("| Value: %s", current->value);
		printf("\n****************************\n");
		current = current->next;
	}
}

t_com	*set_command(t_shell *data_config, char *cmd_line_args)
{
	t_token *token;
	t_com	*com;

	expand(&cmd_line_args, data_config->env, data_config->exit_status);
	token = tokenizer(cmd_line_args, data_config->env, &(data_config->exit_status));
	trim_quotes(&token);
	if (!token)
		return (NULL);
	com = create_cmds(token);
	if (!data_config || !cmd_line_args)
		return (NULL);
	data_config->command = com;
	return (com);
}

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*simple_pwd(char *pwd, char *home)
{
	char	*rest_path;
	char	*simplified;
	int		len;

	if (!home)
		return (pwd);
	len = ft_strlen(home);
	if (ft_strncmp(pwd, home, ft_strlen(home)))
		return (pwd);
	rest_path = ft_substr(pwd, len, ft_strlen(pwd) - len);
	simplified = ft_strjoin("~", rest_path, GLOBAL);
	return (simplified);
}

char *prompt(t_shell *data)
{
	char *cwd = data->pwd;
	char *output;
	t_env	*tmp;

	output = NULL;
	output = ft_strjoin(output, PROMPT_MSG_1, GLOBAL);
	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "HOME"))
			cwd = simple_pwd(cwd, tmp->value);
		tmp = tmp->next;
	}
	output = ft_strjoin(output, cwd, GLOBAL);
	output = ft_strjoin(output, PROMPT_MSG_2, GLOBAL);
	if (data->exit_status != 0)
		output = ft_strjoin(output, UNVALID_ARROW, GLOBAL);
	else
		output = ft_strjoin(output, VALID_ARROW, GLOBAL);
	return (output);
}

int	is_spaces(char *str)
{
	int	i;

	if (!*str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' '
			&& str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
void	disable_echo(struct termios term)
{
	if (!isatty(STDIN_FILENO))
		return ;
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcgetattr");
        gc_free_all(LOCAL);
        gc_free_all(GLOBAL);
		exit(EXIT_FAILURE);
	}
}
	void	p(void)
	{
		system("leaks a.out");
	}


int main(int argc, char *argv[], char **envp)
{
	struct termios	term;
	char	*cmd_line_args;
   	char	**args;
	t_shell	data;

	(void)args;
	(void)argv;
	(void)argc;
	
	// atexit(p);
    if (!init_shell_data_config(&data, envp))
	{
    	fprintf(stderr, "Failed to initialize data\n");
    	return (1);
    }
	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
        gc_free_all(LOCAL);
        gc_free_all(GLOBAL);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		disable_echo(term);
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGKILL, SIG_IGN);
		cmd_line_args = readline(prompt(&data));
		if (!cmd_line_args)
		{
			break ;
		}
		add_history(cmd_line_args);
		if (set_command(&data, cmd_line_args) != NULL && !is_spaces(cmd_line_args))
		{
			if (data.command && data.command->command)
				data.exit_status = ft_execute_command(&data);
		}
		// printf("before\n");
		// system("leaks minishell");
		free(cmd_line_args);
		gc_free_all(LOCAL);
		// printf("after\n");
		// system("leaks minishell");
	}
	gc_free_all(GLOBAL);
	gc_free_all(LOCAL);
	return (0);
}

