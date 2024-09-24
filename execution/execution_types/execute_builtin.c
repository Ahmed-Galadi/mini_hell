/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:48:47 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/18 18:38:05 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_execute_builtin(t_shell *data)
{
	int stdout_copy = -1;

	t_com *command;

	command = data->command;
	if (command->operator)
	{
		if (command->operator->operator == RED_OUT || command->operator->operator == APPEND)
		{
			stdout_copy = dup(STDOUT_FILENO);
			handle_redirections(command);
		}
	}

	if (ft_strcmp(command->command[0], "echo") == 0)
		ft_echo(&command->command[1]);
	else if (ft_strcmp(command->command[0], "env") == 0)
		ft_env(data->env);
	else if (ft_strcmp(command->command[0], "export") == 0)
		ft_export(&command->command[1], data);
	else if (ft_strcmp(command->command[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(command->command[0], "cd") == 0)
		ft_cd(command->command, data);
	else if (ft_strcmp(command->command[0], "unset") == 0)
		ft_unset(&command->command[1], data);
	else if (ft_strcmp(command->command[0], "exit") == 0)
		ft_exit(command->command, data->exit_status);
	if (stdout_copy != -1)
		restore_stdout(stdout_copy);
	return (0);
}
