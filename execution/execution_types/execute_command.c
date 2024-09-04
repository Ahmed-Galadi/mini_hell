/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:50:40 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/04 17:33:25 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void print_token(t_token *token)
{
	t_token *current;

	if (!token)
	{
		printf("empty token!\n");
		return ;
	}
	current = token;
	while (current)
	{
		printf("Type: %d", current->type);
		if (current->value)
			printf("| Value: %s", current->value);
		printf("\n****************************\n");
		current = current->next;
	}
}

void print_opp(t_opp *opera)
{
	t_opp *current;

	if (!opera)
		printf("\tempty operations!\n");
	else
	{
		current = opera;
		while (current)
		{
			printf("\tRedirection Type: %d", current->operator);
			if (current->arg)
				printf("\t | File: %s", current->arg);
			printf("\n\t--------------------------\n");
			current = current->next;
		}	
	}
}

void	print_command(t_com *command)
{
	t_com	*current;
	
	if (!command)
	{
		printf("No Command!\n");
		return ;
	}
	current = command;
	while(current)
	{
		int i = 0;
		printf("args:");
		while ((current->command)[i])
			printf(" %s", (current->command)[i++]);
		printf("\n");
		print_opp(current->operator);
		current = current->next;
	}
}

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
        return result;
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
