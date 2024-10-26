/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:25:49 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/26 00:52:24 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_exit_status(int status)
{
	if (WIFSIGNALED(status))
	{
		 (void)(WTERMSIG(status) == SIGINT);
			// write(1, "\n", 1);
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit: 3\n");
		return (128 + WTERMSIG(status));
	}
	return (WEXITSTATUS(status));
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

static int	handle_child_process(t_shell *data, char ***commands, t_pipe *pipe)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pipe->curr_command == 0)
		pipe->prev_pipe = NULL;
	if (pipe->curr_command == pipe->num_commands - 1)
		pipe->curr_pipe = NULL;
	redirect_to_pipe_fds(data, is_builtin(data->command->command[0]), pipe);
	if (is_builtin(data->command->command[0]))
		ft_execute_builtin(data);
	else
		execute_command(data, commands[pipe->curr_command]);
	exit (0);
}

static int	setup_pipes_and_fork(t_shell *data, char ***commands,
	t_pipe *pipex)
{
	pid_t	pid;
	int		num_commands;

	if (pipex->curr_command < pipex->num_commands - 1)
		if (pipe(pipex->curr_pipe) == -1)
			return (perror("pipe"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	else if (pid == 0)
		handle_child_process(data, commands, pipex);
	return (0);
}

int	ft_execute_pipeline(char ***commands, int num_commands, t_shell *data)
{
	int		status;
	t_pipe	*pipe;

	ft_init_pipe(&pipe, num_commands);
	data->heredoc_index = 0;
	ft_open_heredoc(data);
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
	update_prev_pipe(pipe->prev_pipe, pipe->curr_pipe, 0);
	while (wait(&status) > 0)
		;
	return (set_exit_status(status));
}
