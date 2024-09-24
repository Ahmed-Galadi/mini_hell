/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:25:49 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/16 15:24:57 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void update_prev_pipe(int *prev_pipe, int *curr_pipe, int is_last)
{
	if (prev_pipe[0] != -1)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
	if (is_last)
	{
		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];
	}
}

int set_exit_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit: 3\n");
		return (128 + WTERMSIG(status));
	}
	return (WEXITSTATUS(status));
}

int ft_execute_pipeline(char ***commands, int num_commands, t_shell *data)
{
	int prev_pipe[2] = {-1, -1};
	int curr_pipe[2] = {-1, -1};
	pid_t pid;
	int status;
	int i;

	i = 0;
	while (i < num_commands)
	{
		if (i < num_commands - 1)
			if (pipe(curr_pipe) == -1)
				return (perror("pipe"), 1);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			redirect_to_pipe_fds(data, (i > 0) ? prev_pipe : NULL, (i < num_commands - 1) ? curr_pipe : NULL, i, num_commands);
			if (is_builtin(data->command->command[0]))
				ft_execute_builtin(data);
			execute_command(data, commands[i]);
		}
		update_prev_pipe(prev_pipe, curr_pipe, i < num_commands - 1);
		data->command = data->command->next;
		i++;
	}
	update_prev_pipe(prev_pipe, curr_pipe, 0); /* Close prev_pipe fds */
	while (wait(&status) > 0)
		;
	return (set_exit_status(status));
}
