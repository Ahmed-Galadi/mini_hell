/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:26:37 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/19 00:17:12 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_pipes(t_com *command)
{
	int		count;
	t_com	*curr;

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

void	convert_commands(char ****command_list,
	int num_commands, t_com *current)
{
	int		cmd_index;
	int		i;
	int		arg_count;

	cmd_index = 0;
	while (current && cmd_index < num_commands)
	{
		arg_count = 0;
		while (current->command[arg_count])
			arg_count++;
		(*command_list)[cmd_index] = gc_malloc(sizeof(char *) * (arg_count + 1),
				LOCAL);
		if (!(*command_list)[cmd_index])
			return ;
		i = 0;
		while (i < arg_count)
		{
			(*command_list)[cmd_index][i] = ft_strdup(current->command[i]);
			i++;
		}
		(*command_list)[cmd_index][arg_count] = NULL;
		current = current->next;
		cmd_index++;
	}
	(*command_list)[cmd_index] = NULL;
}

char	***split_commands(t_com *commands, int num_commands)
{
	char	***command_list;
	t_com	*current;

	current = commands;
	command_list = gc_malloc(sizeof(char **) * (num_commands + 1), LOCAL);
	if (!command_list)
		return (NULL);
	convert_commands(&command_list, num_commands, current);
	return (command_list);
}

void	ft_init_pipe(t_pipe **pipe, int num_commands)
{
	if (!(*pipe))
	{
		ft_printf(2, "error in initializing pipe\n");
		return ;
	}
	*pipe = gc_malloc(sizeof(t_pipe), LOCAL);
	if (!*pipe)
		return ;
	(*pipe)->curr_pipe = gc_malloc(sizeof(int) * 2, LOCAL);
	if (!(*pipe)->curr_pipe)
		return ;
	(*pipe)->prev_pipe = gc_malloc(sizeof(int) * 2, LOCAL);
	if (!(*pipe)->prev_pipe)
		return ;
	(*pipe)->pids = gc_malloc(sizeof(pid_t) * num_commands, GLOBAL);
	if (!(*pipe)->pids)
		return ;
	(*pipe)->curr_pipe[0] = -1;
	(*pipe)->curr_pipe[1] = -1;
	(*pipe)->prev_pipe[0] = -1;
	(*pipe)->prev_pipe[1] = -1;
	(*pipe)->num_commands = num_commands;
	(*pipe)->curr_command = 0;
}

void	update_prev_pipe(int *prev_pipe, int *curr_pipe, int is_not_last)
{
	if (prev_pipe[0] != -1)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
		prev_pipe[0] = -1;
		prev_pipe[1] = -1;
	}
	if (is_not_last && curr_pipe)
	{
		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];
		curr_pipe[0] = -1;
		curr_pipe[1] = -1;
	}
}
