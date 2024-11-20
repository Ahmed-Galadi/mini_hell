/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:26:33 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/20 00:00:29 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_files_redirections(t_opp *curr_op, t_shell *data)
{
	int		flags;
	int		default_fd;
	int		redirect_fd;
	char	*file;

	file = curr_op->arg;
	flags = 0;
	redirect_fd = -2;
	if (!valid_operator(curr_op->operator, & flags, &default_fd))
		perror(file);
	if (ft_strcmp(file, "/dev/stdout") != 0)
		redirect_fd = open(file, flags, 0644);
	if (redirect_fd >= 0)
	{
		dup2(redirect_fd, default_fd);
		close(redirect_fd);
	}
	else if (redirect_fd == -1)
	{
		data->exit_status = 1;
		perror(file);
		exit (data->exit_status);
	}
}

void	move_output_to_files(t_shell *data, t_opp *curr_op,
	int *flag_in, int *flag_out)
{
	*flag_in = 0;
	*flag_out = 0;
	if (curr_op && curr_op->operator >= 0)
	{
		while (curr_op)
		{
			if (curr_op->operator == HERE_DOC
				|| curr_op->operator == HERE_DOC_EXP)
				ft_read_from_heredoc(data);
			else
				handle_files_redirections(curr_op, data);
			if (is_redirection_out(curr_op->operator, curr_op->arg))
				*flag_out = 1;
			if (is_redirection_in(curr_op->operator))
				*flag_in = 1;
			curr_op = curr_op->next;
		}
	}
}

void	use_pipe(t_pipe *pipe, int *flag_in, int *flag_out)
{
	if (pipe->curr_command > 0 && !(*flag_in))
	{
		if (pipe->prev_pipe && pipe->prev_pipe[0] != -1)
		{
			if (dup2(pipe->prev_pipe[0], STDIN_FILENO) == -1)
				return (perror("dup2"), exit(1));
		}
	}
	if (pipe->curr_command < pipe->num_commands - 1 && !(*flag_out))
	{
		if (pipe->curr_pipe && pipe->curr_pipe[1] != -1)
		{
			if (dup2(pipe->curr_pipe[1], STDOUT_FILENO) == -1)
				return (perror("dup2"), exit(1));
		}
	}
	*flag_in = 0;
	*flag_out = 0;
}

void	redirect_to_pipe_fds(t_shell *data, t_pipe *pipe)
{
	t_com	*command;
	t_opp	*curr_op;
	int		flag_in;
	int		flag_out;

	command = data->command;
	curr_op = command->operator;
	move_output_to_files(data, curr_op, &flag_in, &flag_out);
	use_pipe(pipe, &flag_in, &flag_out);
	close_pipe_fds(pipe);
}
