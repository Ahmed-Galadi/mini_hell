/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_types.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:16:36 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/20 02:30:35 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_signal_received;

void	restore_std_in_out(int stdout_copy, int stdin_copy)
{
	if (stdout_copy != -1)
	{
		if (dup2(stdout_copy, STDOUT_FILENO) < 0)
		{
			perror("Error restoring stdout");
		}
		close(stdout_copy);
	}
	if (stdin_copy != -1)
	{
		if (dup2(stdin_copy, STDIN_FILENO) < 0)
		{
			perror("Error restoring stdin");
		}
		close(stdin_copy);
	}
}

int	handle_redirections(t_shell *data)
{
	t_com	*command;
	t_opp	*cur_op;

	command = data->command;
	if (!command->operator)
		return (0);
	cur_op = command->operator;
	handle_heredoc(data);
	rm_heredoc_files(data);
	if (g_signal_received)
		(gc_free_all(LOCAL)), (exit(1));
	return (handle_redirection_loop(data, cur_op));
}

int	setup_input_redirection(const char *infile, int is_here_doc, t_shell *data)
{
	int	fd_in;

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

int	setup_output_redirection(const char *outfile, int is_appended)
{
	int	fd_out;

	if (!outfile || is_appended < 0)
		return (1);
	if (access(outfile, F_OK) == 0)
		if (access(outfile, W_OK) != 0)
			return (perror(outfile), 1);
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
