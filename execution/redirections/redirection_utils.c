/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:26:33 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/30 23:26:37 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>

static int is_redirection_out(e_tokenType operator);
static int is_redirection_in(e_tokenType operator);

int valid_operator(e_tokenType operator_type, int *flags, int *default_fd)
{
	if (operator_type == RED_IN)
	{
		*default_fd = STDIN_FILENO;
		*flags = O_RDONLY;
	}
	else if (operator_type == RED_OUT)
	{
		*default_fd = STDOUT_FILENO;
		*flags = O_RDWR | O_CREAT | O_TRUNC;
	}
	else if (operator_type == APPEND)
	{
		*default_fd = STDOUT_FILENO;
		*flags = O_RDWR | O_CREAT | O_APPEND;
	}
	else if (operator_type == HERE_DOC || operator_type == HERE_DOC_EXP)
		return (1);
	else
		return (0); 
	return (1);
}




// void handle_files_redirections(t_opp *curr_op,)
// {
// 	int flags;
// 	int default_fd;
// 	int redirect_fd;
// 	char *file;
// 	int		heredoc_fd;
// 	char	*line;

// 	file = curr_op->arg;
// 	flags = 0;
// 	if (!valid_operator(curr_op->operator, &flags, &default_fd))
// 		perror(file);
// 	if (ft_strcmp(file, "/dev/stdout") != 0)
// 		redirect_fd = open(file, flags, 0644);
// 	if (redirect_fd >= 0)
// 	{
// 		dup2(redirect_fd, default_fd);
// 		close(redirect_fd);
// 	}
// 	else
// 		perror(file);
// }

void handle_files_redirections(t_opp *curr_op)
{
	int flags;
	int default_fd;
	int redirect_fd;
	char *file;

	file = curr_op->arg;
	flags = 0;
	if (!valid_operator(curr_op->operator, &flags, &default_fd))
		perror(file);
	if (ft_strcmp(file, "/dev/stdout") != 0)
		redirect_fd = open(file, flags, 0644);
	if (redirect_fd >= 0)
	{
		dup2(redirect_fd, default_fd);
		close(redirect_fd);
	}
	else
		perror(file);
}

void redirect_to_pipe_fds(t_shell *data, int *prev_pipe, int *curr_pipe, int curr_cmd, int num_commands, int is_builtin)
{
	t_com *command;
	t_opp *curr_op;

	command = data->command;
	curr_op = command->operator;
	int flag_in = 0;
	int flag_out = 0;

	if (curr_op && curr_op->operator >= 0) // User redirections take precedence
	{
		while (curr_op)
		{
			if (curr_op->operator== HERE_DOC
				|| curr_op->operator == HERE_DOC_EXP)
				ft_read_from_heredoc(data);
			else
				handle_files_redirections(curr_op);
			if (is_redirection_out(curr_op->operator))
				flag_out = 1;
			if (is_redirection_in(curr_op->operator))
				flag_in = 1;
			curr_op = curr_op->next;
		}
	}
	/* Handle redirections between pipes*/
	{
		if (curr_cmd > 0 && !flag_in)
		{
			if (dup2(prev_pipe[0], STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
		}
		if (curr_cmd < num_commands - 1 && !flag_out)
		{
			if (dup2(curr_pipe[1], STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
		}
		flag_in = 0;
		flag_out = 0;
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

void close_all_fds(int *fds, int count)
{
	int i = 0;
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

static int is_redirection_out(e_tokenType operator)
{
	if (operator== RED_OUT || operator== APPEND)
		return (1);
	return (0);
}
static int is_redirection_in(e_tokenType operator)
{
	if (operator== RED_IN || operator== HERE_DOC || operator== HERE_DOC_EXP)
		return (1);
	return (0);
}
