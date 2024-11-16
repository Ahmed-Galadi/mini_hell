/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/11/16 19:56:01 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_shell *data, char **cmd_line_args)
{
	while (1)
	{
		data->heredoc_index = 0;
		signals_init(data);
		*cmd_line_args = readline(prompt(data));
		signals_init(data);
		if (!*cmd_line_args)
			break ;
		add_history(*cmd_line_args);
		if (set_command(data, *cmd_line_args)
			&& !is_spaces(*cmd_line_args))
		{
			if (data->command && data->command->command)
				data->exit_status = ft_execute_command(data);
		}
		free(*cmd_line_args);
		gc_free_all(LOCAL);
		data->trap_sigint = 0;
	}
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
	minishell_loop(&data, &cmd_line_args);
	gc_free_all(GLOBAL);
	gc_free_all(LOCAL);
	return (data.exit_status);
}
