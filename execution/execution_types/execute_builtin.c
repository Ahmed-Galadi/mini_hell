/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:48:47 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/28 03:36:27 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

int	copy_stdout(t_shell *data, int *stdout_copy, int *stdin_copy)
{
	t_com	*command;

	*stdout_copy = -1;
	*stdin_copy = -1;
	command = data->command;
	if (command->operator)
	{
		if (command->operator->operator == RED_OUT
			|| command->operator->operator == APPEND)
		{
			*stdout_copy = dup(STDOUT_FILENO);
		}
		if (command->operator->operator == RED_IN)
		{
			*stdin_copy = dup(STDIN_FILENO);
		}
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

	if (data->exit_status)
		data->exit_status = 0;
	if (copy_stdout(data, &stdout_copy, &stdin_copy))
		return (restore_stdout(stdout_copy, stdin_copy), 1);
	command = data->command;
	if (ft_strcmp(command->command[0], "echo") == 0)
		data->exit_status = ft_echo(&command->command[1], data);
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
	if (stdout_copy != -1 || stdin_copy != -1)
		restore_stdout(stdout_copy, stdin_copy);
	return (data->exit_status);
}
