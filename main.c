/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/18 01:02:23 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <sys/signal.h>

void	set_command(t_data *data_config, char *cmd_line_args)
{
	t_token *token;
	t_com	*com;

	token = tokenizer(cmd_line_args);
	com = create_cmds(token);
	if (!data_config || !cmd_line_args)
		return ;
	data_config->command = com;
}

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

int main(int argc, char *argv[], char **envp)
{
	char	*cmd_line_args;
   	char	**args;
	t_data	data;
	int		return_value;

	(void)args;
	(void)argv;
	(void)argc;
	(void)return_value;
    if (!init_data(&data, envp))
	{
    	fprintf(stderr, "Failed to initialize data\n");
    	return (1);
    }
	while (1)
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGKILL, SIG_IGN);
		cmd_line_args = readline(BASH_PROMPT_NAME);
		if (!cmd_line_args)
			break ;
		add_history(cmd_line_args);
		set_command(&data, cmd_line_args);
		//print_command(data.command);
		if (data.command && data.command->command)
			ft_execute_command(data.command, &return_value, &data);
	}
	return (0);
}
