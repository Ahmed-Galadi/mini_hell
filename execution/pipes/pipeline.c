/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:25:49 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/13 17:31:26 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void handle_user_redirections(t_opp *curr_op)
{
	int flags;
	int fd_redirect;
	int	rediflag;
	char	*file;

	rediflag = curr_op->operator;
	file = curr_op->arg;
	if (rediflag == RED_IN)
	{
		flags = O_RDONLY;
		fd_redirect = open(file, flags, 0644);
		if (fd_redirect >= 0)
		{
			dup2(fd_redirect, STDIN_FILENO);
			close(fd_redirect);
		}
		else
			perror("Error opening file for input redirection");
	}
	else if (rediflag == RED_OUT)
	{
		flags = O_RDWR | O_CREAT | O_TRUNC;
		fd_redirect = open(file, flags, 0644);
		if (fd_redirect >= 0)
		{
			dup2(fd_redirect, STDOUT_FILENO);
			close(fd_redirect);
		}
		else
			perror("Error opening file for output redirection");
	}
	else if (rediflag == APPEND)
	{
		// APPEND - TODO later
		printf("");
	}
	else
	{
		// HERE_DOC - TODO later
		printf("");
	}
}

void close_all_fds(int *fds, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (fds[i] != -1)
		{
			close(fds[i]);
			fds[i] = -1;
		}
	}
}

void redirect_files(t_com *command, int *prev_pipe, int *curr_pipe, int curr_cmd, int num_commands)
{
    t_opp *curr_op = command->operator;
	int	flag	= 0;
    if (curr_op && curr_op->operator >= 0) // User redirections take precedence
    {
		flag = 1;
        while (curr_op)
        {
            handle_user_redirections(curr_op);
            curr_op = curr_op->next;
        }
    }
    /* Handle redirections between pipes*/
    {
        if (curr_cmd > 0 && !flag)
        {
            if (dup2(prev_pipe[0], STDIN_FILENO) == -1)
            {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
        }
        if (curr_cmd < num_commands - 1 && !flag)
        {
            if (dup2(curr_pipe[1], STDOUT_FILENO) == -1)
            {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
        }
		flag = 0;
    }
    // Close all pipe file descriptors in the child process
    if (prev_pipe)
    {
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    }
    if (curr_pipe)
    {
        close(curr_pipe[0]);
        close(curr_pipe[1]);
    }
}

int ft_execute_pipeline(char ***commands, int num_commands, int *return_value, t_data *data)
{
    int prev_pipe[2] = {-1, -1};
    int curr_pipe[2] = {-1, -1};
    pid_t pid;
    int status;

    for (int i = 0; i < num_commands; i++)
    {
        if (i < num_commands - 1)
        {
            if (pipe(curr_pipe) == -1)
            {
                perror("pipe");
                return 1;
            }
        }
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            return 1;
        }
        else if (pid == 0)
        {
            redirect_files(data->command, (i > 0) ? prev_pipe : NULL, (i < num_commands - 1) ? curr_pipe : NULL, i, num_commands);
            execute_command(data, commands[i]);
            exit(EXIT_FAILURE);
        }
        if (prev_pipe[0] != -1)
        {
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }
        if (i < num_commands - 1)
        {
            prev_pipe[0] = curr_pipe[0];
            prev_pipe[1] = curr_pipe[1];
        }
        data->command = data->command->next;
    }
    if (prev_pipe[0] != -1)
    {
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    }
    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            *return_value = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            *return_value = 128 + WTERMSIG(status);
    }
    return 0;
}
