/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:25:49 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/29 19:01:00 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <readline/readline.h>
#include <sys/fcntl.h>
#include <unistd.h>

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

int heredoc_one_pipe(t_com *command)
{
    t_opp *curr_op;
    int count_heredocs;
    if (!command)
        return (0);

    curr_op = command->operator;
    count_heredocs = 0;
    while (curr_op)
    {
        if (curr_op->operator == HERE_DOC)
            count_heredocs++;
        curr_op = curr_op->next;
    }
    return (count_heredocs);
}

int ft_execute_pipeline(char ***commands, int num_commands, t_shell *data)
{
    int prev_pipe[2] = {-1, -1};
    int curr_pipe[2] = {-1, -1};
    pid_t pid;
    int status;
    int i;
    t_com *com;
    t_opp *curr_op;

    i = 0;
    data->heredoc_index = 0;
    ft_open_heredoc(data);
    while (i < num_commands)
    {
        com = &data->command[i];
        curr_op = com->operator;

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
            redirect_to_pipe_fds(data, (i > 0) ? prev_pipe : NULL, (i < num_commands - 1) ? curr_pipe : NULL, i, num_commands, is_builtin(data->command->command[0]));
            if (is_builtin(data->command->command[0]))
                ft_execute_builtin(data);
            else
                execute_command(data, commands[i]);
            exit(0);
        }
        data->heredoc_index += heredoc_one_pipe(data->command);
        update_prev_pipe(prev_pipe, curr_pipe, i < num_commands - 1);
        data->command = data->command->next;
        i++;
    }

    update_prev_pipe(prev_pipe, curr_pipe, 0);
    while (wait(&status) > 0)
        ;
    return (set_exit_status(status));
}
