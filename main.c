/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/10 15:49:37 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
