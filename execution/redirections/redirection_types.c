/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_types.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:16:36 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/25 16:58:08 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

void	handle_redirections(t_shell *data)
{
	t_com *command;

	if (!data)
		return ;
	command = data->command;
    if (!command || !command->operator)
        return ;

    t_opp *current_op = command->operator;

    while (current_op)
    {
        if (current_op->operator == RED_OUT)
        {
            setup_output_redirection(current_op->arg, 0);
        }
        else if (current_op->operator == APPEND)
        {
            setup_output_redirection(current_op->arg, 1);
        }
        else if (current_op->operator == RED_IN)
        {
            setup_input_redirection(current_op->arg, 0, data);
        }
        else if (current_op->operator == HERE_DOC)
        {
            setup_input_redirection(current_op->arg, 1, data);
        }
        else
        {
            fprintf(stderr, "Unhandled redirection type: %d\n", current_op->operator);
        }

        current_op = current_op->next;
    }
}



void setup_input_redirection(const char *infile, int is_here_doc, t_shell *data)
{
	int fd_in;
	int pipe_fds[2];

	if (!infile)
		return;

	if (is_here_doc)
	{
		ft_open_heredoc(data);
		ft_read_from_heredoc(data);
	}
	else
	{
		// Standard input redirection from a file
		fd_in = open(infile, O_RDONLY);
		if (fd_in < 0)
		{
			perror("Error opening infile for input redirection");
			return;
		}

		if (dup2(fd_in, STDIN_FILENO) < 0)
		{
			perror("Error duplicating file descriptor for input redirection");
			close(fd_in);
			return;
		}

		close(fd_in);
	}
}

void setup_output_redirection(const char *outfile, int is_appended)
{
    int fd_out;
    int stdout_copy;

    if (!outfile || is_appended < 0)
        return;

    // Save the current stdout
    stdout_copy = dup(STDOUT_FILENO);
    if (stdout_copy < 0)
    {
        perror("Error saving stdout");
        return;
    }

    if (is_appended)
        fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0666);
    else
        fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0666);
        
    if (fd_out < 0)
    {
        perror("Error opening outfile for output redirection");
        return;
    }

    if (dup2(fd_out, STDOUT_FILENO) < 0)
    {
        perror("Error duplicating file descriptor for output redirection");
        close(fd_out);
        return;
    }


    close(fd_out);

}

void	restore_stdout(int stdout_copy)
{
    if (dup2(stdout_copy, STDOUT_FILENO) < 0)
    {
        perror("Error restoring stdout");
    }
    close(stdout_copy);
}
