/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:48:47 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/09 22:28:14 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	copy_std_in_out(t_shell *data, int *stdout_copy, int *stdin_copy)
{
	t_com	*command;

	*stdout_copy = dup(STDOUT_FILENO);
	*stdin_copy = dup(STDIN_FILENO);
	command = data->command;
	if (command->operator)
	{
		data->exit_status = handle_redirections(data);
		return (data->exit_status);
	}
	return (0);
}

int	ft_execute_builtin(t_shell *data)
{
	t_com	*command;
	int		stdout_copy;
	int		stdin_copy;

	if (copy_std_in_out(data, &stdout_copy, &stdin_copy))
		return (restore_std_in_out(stdout_copy, stdin_copy), 1);
	command = data->command;
	if (ft_strcmp(command->command[0], "echo") == 0)
		data->exit_status = ft_echo(&command->command[1]);
	else if (ft_strcmp(command->command[0], "env") == 0)
		data->exit_status = ft_env(data->env);
	else if (ft_strcmp(command->command[0], "export") == 0)
		data->exit_status = ft_export(&command->command[1], data);
	else if (ft_strcmp(command->command[0], "pwd") == 0)
		data->exit_status = ft_pwd(data);
	else if (ft_strcmp(command->command[0], "cd") == 0)
		data->exit_status = ft_cd(command->command, data);
	else if (ft_strcmp(command->command[0], "unset") == 0)
		data->exit_status = ft_unset(&command->command[1], data);
	else if (ft_strcmp(command->command[0], "exit") == 0)
		data->exit_status = ft_exit(command->command, data->exit_status);
	restore_std_in_out(stdout_copy, stdin_copy);
	return (data->exit_status);
}
