/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:50:40 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/28 02:38:45 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_execute_command(t_shell *data)
{
	int		pipe_count;
	t_com	*command;
	char	***commands;
	int		result;
	int		stdin_copy;

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
			data->exit_status = ft_execute_builtin(data);
		else
			return (ft_execute_external(command->command, data, command));
	}
	return (data->exit_status);
}

static char	*get_full_path(char *path, const char *cmd)
{
	char	*full_path;
	char	**paths;
	char	*tmp;
	int		i;

	paths = cstm_split(path, ":");
	i = 0;
	while (paths[i])
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return ((char *)cmd);
		tmp = ft_strjoin(paths[i], "/", LOCAL);
		full_path = ft_strjoin(tmp, cmd, LOCAL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

const char	*get_path(const char *cmd, t_env *env)
{
	int		i;
	char	*value;
	t_env	*curr;

	if (ft_strcmp(cmd, "") == 0)
		return (NULL);
	if (!cmd || !env)
		return (NULL);
	if (cmd[0] == '/')
		return (cmd);
	value = ft_get_var_value(env, "PATH");
	if (!value)
	{
		printf("%s: No such file or directory\n", cmd);
		return (exit (127), NULL);
	}
	return (get_full_path(value, cmd));
}

void	execute_command(t_shell *data, char **commands)
{
	const char	*full_path;

	if (!commands[0])
		return ;
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
		exit(127);
	}
}
