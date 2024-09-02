/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:50:40 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/27 15:42:59 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int ft_execute_external_no_fork(char **args, int *return_value, t_data *data)
// {
//     char **env_array = env_to_array(data->env);
//     if (!env_array)
//     {
//         fprintf(stderr, "Failed to create environment array\n");
//         exit(1);
//     }
//     char *cmd_path = find_command(args[0], env_array);
//     if (!cmd_path)
//     {
//         fprintf(stderr, "Command not found: %s\n", args[0]);
//         *return_value = 127;
//         exit(127);  // Exit with 127 for command not found
//     }
//     if (execve(cmd_path, args, env_array) == -1)
//     {
//         perror("Error execve");
//         *return_value = 126;
//         exit(126);  // Exit with 126 for execution error
//     }
//     *return_value = 0;
//     return 0;  // This line should never be reached
// }

// int ft_execute_command(char **args, int *return_value, t_data *data, int is_piped)
// {
//     int builtin_status;
    
//     if (*args == NULL)
//         return (1);

//     builtin_status = ft_execute_builtin(args, return_value, data);
//     if (builtin_status != -1)
//     {
//         return (builtin_status);
//     }
//     else
//     {
//         if (is_piped)
//         {
//             return (ft_execute_external_no_fork(args, return_value, data));
//         }
//         else
//         {
//             return (ft_execute_external(args, return_value, data));
//         }
//     }
// }

int ft_execute_command(char **args, int *return_value, t_data *data)
{
    int builtin_status;
    int pipe_count;
    
    if (*args == NULL)
        return (1);
    // Check if the command contains pipes
    pipe_count = count_pipes(args);
    if (pipe_count > 0)
    {
        char ***commands = split_commands(args, pipe_count + 1);
        int result = ft_execute_pipeline(commands, pipe_count + 1, return_value, data);
        // Free commands array
        free_commands(commands, pipe_count + 1);
        return result;
    }
    else
    { 
        builtin_status = ft_execute_builtin(args, return_value, data);
        if (builtin_status != -1)
        {
            //printf("execute builtin called\n");
            return (builtin_status);
        }
        else
        {
            //printf("execute external called\n");
            return (ft_execute_external(args, return_value, data));
        }
    }
}
