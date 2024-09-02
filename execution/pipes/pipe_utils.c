/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:26:37 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/26 17:39:12 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int count_pipes(char **args)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (args[i])
    {
        if (ft_strcmp(args[i], "|") == 0)
            count++;
        i++;
    }
    return (count);
}

char ***split_commands(char **args, int num_commands)
{
    int cmd_index;
    int arg_index;
    int i;
    char ***commands;
    
    cmd_index = 0;
    arg_index = 0;
    i = 0;
    commands = malloc(sizeof(char **) * num_commands);
    commands[cmd_index] = malloc(sizeof(char *) * (count_args_until_pipe(args) + 1));
    while (args[i])
    {
        if (ft_strcmp(args[i], "|") == 0)
        {
            commands[cmd_index][arg_index] = NULL;
            cmd_index++;
            arg_index = 0;
            commands[cmd_index] = malloc(sizeof(char *) * (count_args_until_pipe(args + i + 1) + 1));
        }
        else
        {
            commands[cmd_index][arg_index] = ft_strdup(args[i]);
            arg_index++;
        }
        i++;
    }
    commands[cmd_index][arg_index] = NULL;
    return (commands);
}

int count_args_until_pipe(char **args)
{
    int count = 0;
    while (args[count] && ft_strcmp(args[count], "|") != 0)
        count++;
    return count;
}

void    free_commands(char ***commands, int num_commands)
{
    int i;
    int j;

    i = 0;
    while (i < num_commands)
    {
        j = 0;
        while (commands[i][j])
        {
            free(commands[i][j]);
            j++;
        }
        free(commands[i]);
        i++;
    }
    free(commands);
}