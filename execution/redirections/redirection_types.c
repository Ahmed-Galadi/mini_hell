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
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <unistd.h>

int	handle_redirections(t_shell *data)
{
	int		s;
	t_com	*command;

	if (!data)
		return (1);
	command = data->command;
    if (!command->operator)
        return (0);
    t_opp *current_op = command->operator;
	ft_open_heredoc(data);
	s = 0;
    while (current_op)
    {
		if (s)
		{
			data->exit_status = s;
			return (s);
		}
        if (current_op->operator == RED_OUT)
            s = setup_output_redirection(current_op->arg, 0, data);
        else if (current_op->operator == APPEND)
        {
            s = setup_output_redirection(current_op->arg, 1, data);
        }
        else if (current_op->operator == RED_IN)
        {
            s = setup_input_redirection(current_op->arg, 0, data);
        }
        else if (current_op->operator == HERE_DOC
				|| current_op->operator == HERE_DOC_EXP)
        {
            s = setup_input_redirection(current_op->arg, 1, data);
        }
        else
        {
            fprintf(stderr, "Unhandled redirection type: %d\n", current_op->operator);
        }
        current_op = current_op->next;
    }
	data->exit_status = s;
	return (data->exit_status);
}

int setup_input_redirection(const char *infile, int is_here_doc, t_shell *data)
{
	int fd_in;
	int pipe_fds[2];

	if (!infile)
		return (1);
	if (is_here_doc)
	{
		ft_read_from_heredoc(data);
	}
	else
	{
		fd_in = open(infile, O_RDONLY);
		if (fd_in < 0)
		{
			perror(infile);
			return (1);
		}
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

int setup_output_redirection(const char *outfile, int is_appended, t_shell *data)
{
    int fd_out;
    int stdout_copy;

    if (!outfile || is_appended < 0)
        return (1);

    stdout_copy = dup(STDOUT_FILENO);
    if (stdout_copy < 0)
    {
        perror("Error saving stdout");
        return (1);
    }
	if (access(outfile, F_OK) == 0)
	{
		fd_out = open(outfile, O_RDONLY);
		if (fd_out < 0)
			printf("Error: Permission \n" );
        return (1);
	}
    if (is_appended)
        fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0666);
    else
        fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
        
    if (fd_out < 0)
    {
        perror("Error opening outfile for output redirection");
        return (1);
    }
    if (dup2(fd_out, STDOUT_FILENO) < 0)
    {
        perror("Error duplicating file descriptor for output redirection");
        close(fd_out);
        return (1);
    }
    close(fd_out);
	return (0);
}

void	restore_stdout(int stdout_copy)
{
    if (dup2(stdout_copy, STDOUT_FILENO) < 0)
    {
        perror("Error restoring stdout");
    }
    close(stdout_copy);
}
