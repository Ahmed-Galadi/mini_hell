/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:26:37 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/07 18:17:29 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int count_pipes(t_com *command)
{
	int count;
	t_com *curr;

	if (!command)
		return (0);
	count = 0;
	curr = command;
	while (curr->next)
	{
		++count;
		curr = curr->next;
	}
	return (count);
}

char	***split_commands(t_com *commands, int num_commands)
{
	char ***command_list;
	int cmd_index;
	int	i;
	t_com *current = commands;

	// Allocate memory for the command list
	command_list = gc_malloc(sizeof(char **) * (num_commands + 1), LOCAL);
	if (!command_list)
		return NULL;

	cmd_index = 0;
	// Iterate through the commands
	while (current && cmd_index < num_commands)
	{
		int arg_count = 0;
		while (current->command[arg_count])
			arg_count++;

		// Allocate memory for the command and its arguments
		command_list[cmd_index] = gc_malloc(sizeof(char *) * (arg_count + 1), LOCAL);
		if (!command_list[cmd_index])
			return NULL;

		// Copy the command and arguments
		i = 0;
		while (i < arg_count)
		{
			command_list[cmd_index][i] = ft_strdup(current->command[i]);
			i++;
		}
		command_list[cmd_index][arg_count] = NULL;

		// Move to the next command
		current = current->next;
		cmd_index++;
	}

	// Null-terminate the list of commands
	command_list[cmd_index] = NULL;

	return command_list;
}

// void    free_commands(char ***commands, int num_commands)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < num_commands)
// 	{
// 		j = 0;
// 		while (commands[i][j])
// 		{
// 			free(commands[i][j]);
// 			j++;
// 		}
// 		free(commands[i]);
// 		i++;
// 	}
// 	free(commands);
// }