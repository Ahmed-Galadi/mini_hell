/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_types.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:16:36 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/04 11:29:02 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	restore_stdout(int stdout_copy)
{
	if (dup2(stdout_copy, STDOUT_FILENO) < 0)
	{
		perror("Error restoring stdout");
	}
	close(stdout_copy);
}

int	handle_redirections(t_shell *data)
{
	t_com	*command;
	t_opp	*cur_op;

	command = data->command;
	if (!command->operator)
		return (0);
	cur_op = command->operator;
	ft_open_heredoc(data);
	while (cur_op)
	{
		if (data->exit_status)
			return (data->exit_status);
		if (cur_op->operator == RED_OUT)
			data->exit_status = setup_output_redirection(cur_op->arg, 0, data);
		else if (cur_op->operator == APPEND)
			data->exit_status = setup_output_redirection(cur_op->arg, 1, data);
		else if (cur_op->operator == RED_IN)
			data->exit_status = setup_input_redirection(cur_op->arg, 0, data);
		else if (cur_op->operator == HERE_DOC
			|| cur_op->operator == HERE_DOC_EXP)
			data->exit_status = setup_input_redirection(cur_op->arg, 1, data);
		cur_op = cur_op->next;
	}
	return (data->exit_status);
}

int	setup_input_redirection(const char *infile, int is_here_doc, t_shell *data)
{
	int	fd_in;
	int	pipe_fds[2];

	if (!infile)
		return (1);
	if (is_here_doc)
		ft_read_from_heredoc(data);
	else
	{
		fd_in = open(infile, O_RDONLY);
		if (fd_in < 0)
			return (perror(infile), 1);
		if (dup2(fd_in, STDIN_FILENO) < 0)
		{
			perror("dup2");
			close(fd_in);
			return (1);
		}
		close(fd_in);
	}
	return (0);
}

int	setup_output_redirection(const char *outfile, int is_appended,
		t_shell *data)
{
	int	fd_out;
	int	stdout_copy;

	if (!outfile || is_appended < 0)
		return (1);
	stdout_copy = dup(STDOUT_FILENO);
	if (stdout_copy < 0)
		return (perror("dup"), 1);
	if (access(outfile, F_OK) == 0)
		if (access(outfile, W_OK) != 0)
			return (printf("%s: Permission denied\n", outfile), 1);
	if (is_appended)
		fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else
		fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd_out < 0)
		return (perror("open"), 1);
	if (dup2(fd_out, STDOUT_FILENO) < 0)
	{
		perror("Error duplicating file descriptor for output redirection");
		close(fd_out);
		return (1);
	}
	close(fd_out);
	return (0);
}

void	close_all_fds(int *fds, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (fds[i] != -1)
		{
			close(fds[i]);
			fds[i] = -1;
		}
		i++;
	}
}
