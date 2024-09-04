/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:50:40 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/04 15:33:25 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
