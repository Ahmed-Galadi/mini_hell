/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:00:18 by agaladi           #+#    #+#             */
/*   Updated: 2024/11/20 02:45:48 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Parent process closes previous pipe after fork
void	close_afrer_fork(t_pipe *pipex)
{
	if (pipex->curr_command > 0 && pipex->prev_pipe)
	{
		close(pipex->prev_pipe[0]);
		close(pipex->prev_pipe[1]);
		pipex->prev_pipe[0] = -1;
		pipex->prev_pipe[1] = -1;
	}
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

static void	close_prev_pipe(t_pipe *pipe)
{
	if (pipe->prev_pipe)
	{
		if (pipe->prev_pipe[0] != -1)
		{
			close(pipe->prev_pipe[0]);
			pipe->prev_pipe[0] = -1;
		}
		if (pipe->prev_pipe[1] != -1)
		{
			close(pipe->prev_pipe[1]);
			pipe->prev_pipe[1] = -1;
		}
	}
}

static void	close_curr_pipe(t_pipe *pipe)
{
	if (pipe->curr_pipe)
	{
		if (pipe->curr_pipe[0] != -1)
		{
			close(pipe->curr_pipe[0]);
			pipe->curr_pipe[0] = -1;
		}
		if (pipe->curr_pipe[1] != -1)
		{
			close(pipe->curr_pipe[1]);
			pipe->curr_pipe[1] = -1;
		}
	}
}

void	close_pipe_fds(t_pipe *pipe)
{
	close_prev_pipe(pipe);
	close_curr_pipe(pipe);
}
