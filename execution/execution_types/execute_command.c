/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:50:40 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/06 07:48:04 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_execute_command(t_shell *data)
{
	int		pipe_count;
	t_com	*command;
	char	***commands;

	command = data->command;
	if (!command)
		return (1);
	pipe_count = count_pipes(command);
	if (pipe_count > 0)
	{
		commands = split_commands(command, pipe_count + 1);
		data->exit_status = ft_execute_pipeline(commands, pipe_count + 1, data);
		return (data->exit_status);
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

void	ft_is_directory(const char *cmd)
{
	struct stat	sb;
	int			i;

	i = stat(cmd, &sb);
	if (!i && S_ISDIR(sb.st_mode))
	{
		ft_printf(2, "%s: ", cmd);
		ft_printf(2, "is a directory\n");
		gc_free_all(LOCAL);
		exit(126);
	}
}

static char	*get_full_path(char *path, const char *cmd)
{
	char	*full_path;
	char	**paths;
	char	*tmp;
	int		i;

	paths = cstm_split(path, ":");
	i = 0;
	ft_is_directory(cmd);
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/", LOCAL);
		full_path = ft_strjoin(tmp, cmd, LOCAL);
		if (access(full_path, F_OK | X_OK) == 0)
			return ((char *)full_path);
		i++;
		if (!paths[i])
		{
			ft_printf(2, "%s: Command not found\n", cmd);
			return (exit (127), NULL);
		}
	}
	return ((char *) cmd);
}

const char	*get_path(const char *cmd, t_env *env)
{
	char	*value;

	if (ft_strcmp(cmd, "") == 0)
		return (NULL);
	if (!cmd || !env)
		return (NULL);
	if (cmd[0] == '/')
		return (cmd);
	value = ft_get_var_value(env, "PATH");
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
		gc_free_all(LOCAL);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_printf(2, "command not found: %s\n", commands[0]);
		gc_free_all(LOCAL);
		exit(127);
	}
}
