/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:25:49 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/19 00:00:54 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_signal_received;

int	set_exit_status(int *status)
{
	if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == SIGPIPE)
			return (0);
		if (WTERMSIG(*status) == SIGINT)
			printf("\n");
		if (WTERMSIG(*status) == SIGQUIT)
			printf("Quit: 3\n");
		return (128 + WTERMSIG(*status));
	}
	return (WEXITSTATUS(*status));
}

int	heredoc_one_pipe(t_com *command)
{
	t_opp	*curr_op;
	int		count_heredocs;

	if (!command)
		return (0);
	curr_op = command->operator;
	count_heredocs = 0;
	while (curr_op)
	{
		if (curr_op->operator == HERE_DOC || curr_op->operator == HERE_DOC_EXP)
			count_heredocs++;
		curr_op = curr_op->next;
	}
	return (count_heredocs);
}

static void	close_pipe(int *pipe_fd)
{
	if (!pipe_fd)
		return ;
	if (pipe_fd[0] != -1)
	{
		close(pipe_fd[0]);
		pipe_fd[0] = -1;
	}
	if (pipe_fd[1] != -1)
	{
		close (pipe_fd[1]);
		pipe_fd[1] = -1;
	}
}

static int	handle_child_process(t_shell *data, char ***commands, t_pipe *pipe)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pipe->curr_command == 0)
		pipe->prev_pipe = NULL;
	if (pipe->curr_command == pipe->num_commands - 1)
		pipe->curr_pipe = NULL;
	redirect_to_pipe_fds(data, pipe);
	if (is_builtin(data->command->command[0]))
		ft_execute_builtin(data);
	else
		execute_command(data, commands[pipe->curr_command]);
	exit (0);
}

static int setup_pipes_and_fork(t_shell *data, char ***commands, t_pipe *pipex)
{
	pid_t	pid;	
	// Create new pipe for all but the last command
	if (pipex->curr_command < pipex->num_commands - 1)
	{
		if (pipe(pipex->curr_pipe) == -1)
			return (perror("pipe"), 1);
	}

	pid = fork();
	if (pid < 0)
		return (perror("fork"), killall(pipex), 1);
	else if (pid == 0)
	{
		if (pipex->curr_command == 0)
		    pipex->prev_pipe = NULL;  // First command doesn't need prev_pipe
		if (pipex->curr_command == pipex->num_commands - 1)
		    pipex->curr_pipe = NULL;  // Last command doesn't need curr_pipe
		
		handle_child_process(data, commands, pipex);
		exit(1);
	}
	
	pipex->pids[pipex->curr_command] = pid;
	
	// Parent process closes previous pipe after fork
	if (pipex->curr_command > 0 && pipex->prev_pipe)
	{
	    close(pipex->prev_pipe[0]);
	    close(pipex->prev_pipe[1]);
	    pipex->prev_pipe[0] = -1;
	    pipex->prev_pipe[1] = -1;
	}
	
	return (0);
}

int	ft_execute_pipeline(char ***commands, int num_commands, t_shell *data)
{
	int		status;
	t_pipe	*pipe;

	ft_init_pipe(&pipe, num_commands);
	data->heredoc_index = 0;
	handle_heredoc(data);
	if (g_signal_received)
		return (1);
	while (pipe->curr_command < pipe->num_commands)
	{
		if (setup_pipes_and_fork(data, commands, pipe) != 0)
			return (1);
		data->heredoc_index += heredoc_one_pipe(data->command);
		update_prev_pipe(pipe->prev_pipe, pipe->curr_pipe,
			pipe->curr_command < pipe->num_commands - 1);
		data->command = data->command->next;
		pipe->curr_command++;
	}
	close_pipe(pipe->prev_pipe);
    close_pipe(pipe->curr_pipe);
	while (wait(&status) > 0)
		;
	return (set_exit_status(&status));
}
