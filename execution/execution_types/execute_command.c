/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:50:40 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/09 11:40:53 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_execute_command(t_shell *data)
{
	int		builtin_status;
	int		pipe_count;
	t_com	*command;
	char	***commands;
	int		result;

	command = data->command;
	if (!command)
		return (1);
	pipe_count = count_pipes(command);
	if (pipe_count > 0)
	{
		commands = split_commands(command, pipe_count + 1);
		result = ft_execute_pipeline(commands, pipe_count + 1, data);
		return (result);
	}
	else
	{
		if (is_builtin(data->command->command[0]))
			builtin_status = ft_execute_builtin(data);
		else
			return (ft_execute_external(command->command, data, command));
	}
	return (0);
}

const char	*get_path(const char *cmd, t_env *env)
{
	int		i;
	char	**executables;
	char	*with_back_slash;
	char	*full_path;
	char	*key;
	t_env	*curr;

	executables = NULL;
	if (cmd[0] == '/')
		return (cmd);
	if (!cmd || !env)
		return (NULL);
	key = ft_get_var_value(env, "PATH");
	if (!key)
		return (NULL);
	executables = cstm_split(key, ":");
	i = 0;
	while (executables[i])
	{
		with_back_slash = ft_strjoin(executables[i], "/", LOCAL);
		full_path = ft_strjoin(with_back_slash, cmd, LOCAL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

void	execute_command(t_shell *data, char **commands)
{
	const char	*full_path;

	full_path = get_path(commands[0], data->env);
	if (full_path != NULL)
	{
		execve(full_path, commands, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		fprintf(stderr, "Command not found: %s\n", commands[0]);
		exit(EXIT_FAILURE);
	}
}
