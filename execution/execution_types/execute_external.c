/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:51:20 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/25 23:10:07 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_execute_external(char **args, int *return_value, t_data *data)
{
    pid_t pid;
    char *cmd_path;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("Fork Error");
        return 1;
    }
    if (pid == 0)
    {
        // Child process
        char **env_array = env_to_array(data->env);
        if (!env_array)
        {
            fprintf(stderr, "Failed to create environment array\n");
            exit(1);
        }
        cmd_path = find_command(args[0], env_array);
        if (!cmd_path)
        {
            fprintf(stderr, "Command not found: %s\n", args[0]);
            exit(127);  // Exit with 127 for command not found
        }
        if (execve(cmd_path, args, env_array) == -1)
        {
            perror("Error execve");
            exit(126);  // Exit with 126 for execution error
        }
    }
    else
    {
        // Parent process
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("Waitpid Error");
            return 1;
        }
        
        if (WIFEXITED(status))
        {
            *return_value = WEXITSTATUS(status);
        }
        else if (WIFSIGNALED(status))
        {
            *return_value = 128 + WTERMSIG(status);
        }
    }
    return (*return_value);
}