/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:50:40 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/14 12:34:32 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_execute_command(t_com *command, int *return_value, t_data *data)
{
    int builtin_status;
    int pipe_count;

    if (!command)
        return (1);
    // Check if the command contains pipes
    pipe_count = count_pipes(command);
    if (pipe_count > 0)
    {
        char ***commands = split_commands(command, pipe_count + 1);
        int result = ft_execute_pipeline(commands, pipe_count + 1, return_value, data);
        // Free commands array
		// I will use gc
       // free_commands(commands, pipe_count + 1);
        return (result);
    }
    else
    { 
        builtin_status = ft_execute_builtin(command->command, return_value, data, command);
        if (builtin_status != -1)
        {
            //printf("execute builtin called\n");
            return (builtin_status);
        }
        else
        {
            //printf("execute external called\n");
            return (ft_execute_external(command->command, return_value, data, command));
        }
    }
}

const char *get_path(const char *cmd, t_env *env)
{
	int i;
	char **executables;
	char *with_back_slash;
	char *full_path;
	t_env *curr;

	executables = NULL;
	if (!cmd || !env)
		return (NULL);
	curr = env;
	while (curr->next)
	{
		if (ft_strncmp(curr->key, "PATH", 4) == 0)
		{
			executables = ft_split(curr->value, ':');
			break;
		}
		curr = curr->next;
	}
	i = 0;
	while (executables[i])
	{
		with_back_slash = ft_strjoin(executables[i], "/");
		full_path = ft_strjoin(with_back_slash, cmd);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

void execute_command(t_data *data, char **commands)
{
	const char *full_path;

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
