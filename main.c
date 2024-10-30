/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/10/28 03:35:52 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_com	*set_command(t_shell *data_config, char *cmd_line_args)
{
	t_token	*token;
	t_com	*com;

	expand(&cmd_line_args, data_config->env, &data_config->exit_status);
	token = tokenizer(cmd_line_args,
			data_config->env, &(data_config->exit_status));
	if (!token)
		return (NULL);
	com = create_cmds(token);
	if (!data_config || !cmd_line_args)
		return (NULL);
	data_config->command = com;
	return (com);
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
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcgetattr");
		gc_free_all(LOCAL);
		gc_free_all(GLOBAL);
		exit(EXIT_FAILURE);
	}
}

int	g_exit_status = 0;

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals_init(t_shell *data, struct termios term)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	if (g_exit_status == 1)
	{
		data->trap_sigint = 1;
		data->exit_status = 1;
	}
	g_exit_status = 0;
}

int	main(int argc, char *argv[], char **envp)
{
	char			*cmd_line_args;
	char			**args;
	struct termios	term;
	t_shell			data;

	(void)args;
	(void)argv;
	(void)argc;
	data.trap_sigint = 0;
	init_shell_data_config(&data, envp);
	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &term) == -1)
		{
			perror("tcgetattr");
			gc_free_all(LOCAL);
			gc_free_all(GLOBAL);
			exit(EXIT_FAILURE);
		}
		disable_echo(term);
	}
	while (1)
	{
		data.heredoc_index = 0;
		signals_init(&data, term);
		cmd_line_args = readline(prompt(&data));
		signals_init(&data, term);
		if (!cmd_line_args)
			break ;
		add_history(cmd_line_args);
		if (set_command(&data, cmd_line_args) && !is_spaces(cmd_line_args))
		{
			if (data.command && data.command->command)
				data.exit_status = ft_execute_command(&data);
		}
		free(cmd_line_args);
		gc_free_all(LOCAL);
		data.trap_sigint = 0;
	}
	gc_free_all(GLOBAL);
	gc_free_all(LOCAL);
	return (0);
}
