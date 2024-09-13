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

const char *get_path(const char *cmd, t_env *env)
{
	int i;
	char **executables;
	char *with_back_slash;
	char *full_path;
	t_env *curr;

	executables = NULL;
	if (!cmd || !env)
		return (NULL);
	curr = env;
	while (curr->next)
	{
		if (ft_strncmp(curr->key, "PATH", 4) == 0)
		{
			executables = ft_split(curr->value, ':');
			break;
		}
		curr = curr->next;
	}
	i = 0;
	while (executables[i])
	{
		with_back_slash = ft_strjoin(executables[i], "/");
		full_path = ft_strjoin(with_back_slash, cmd);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}

void redirections(t_opp *operator)
{
	t_opp *op;

	op = operator;
	if (!operator)
		return;
	while (op)
	{
		if (op->operator== RED_OUT)
		{
			int fd_out = open(op->arg, O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		if (op->operator== APPEND)
		{
			int fd_out = open(op->arg, O_CREAT | O_RDWR | O_APPEND, 0644);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		op = op->next;
	}
}

void execute_command(t_data *data, char **commands)
{
	const char *full_path;

	full_path = get_path(commands[0], data->env);
	if (full_path != NULL)
	{
		execve(full_path, commands, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		fprintf(stderr, "Command not found: %s\n", commands[0]);
		exit(EXIT_FAILURE);
	}
}

void redirect_files2(t_com *command, int *fd, int curr_cmd, int num_commands)
{
	(void)num_commands;
	(void)command;

	// t_opp *curr_op = command->operator;
	// int flags, fd_redir = -1;
	// Redirect input from previous command if not the first command
	// if (curr_cmd > 0 && fd[0] != -1)
	//     dup2(fd[0], STDIN_FILENO);

	// Redirect output to next command if not the last command
	// if (curr_cmd < num_commands - 1 && fd[1] != -1)
	// {
	// 	while (curr_op)
	// 	{
	// 		if (command->operator->operator == RED_OUT)
	// 			dup2(fd_redir, STDOUT_FILENO);
	// 		curr_op = curr_op->next;
	// 	}
	// }
	if (curr_cmd > 0)
		dup2(fd[0], STDIN_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);

	// curr_op = command->operator;
	//  Handle redirection operators
	//  while (curr_op)
	//  {
	//      if (curr_op->operator)
	//      {
	//          // int flags, fd_redir = -1;
	//          if (curr_op->operator)
	//          {
	//              if (RED_IN == curr_op->operator)
	//  			{
	//                  fd_redir = open(curr_op->arg, O_RDONLY);
	//                  dup2(fd_redir, STDIN_FILENO);
	//                  break;
	//  			}
	//              if (RED_OUT == curr_op->operator)
	//  			{
	//              	flags = O_WRONLY | O_CREAT | O_TRUNC;
	//                  fd_redir = open(curr_op->arg, flags, 0644);
	//                  dup2(fd_redir, STDOUT_FILENO);
	//  			}

	//         }
	//         if (fd_redir != -1)
	//             close(fd_redir);
	//     }
	//     curr_op = curr_op->next;
	// }
}

void handle_user_redirections(t_com *command, e_tokenType rediflag, int *fd)
{
	int flags;
	int fd_redirect;
	(void)fd;
	if (!command)
		return;

	if (rediflag == RED_IN)
	{
		flags = O_RDONLY;
		fd_redirect = open(command->operator->arg, flags, 0777);
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
		fd_redirect = open(command->operator->arg, flags, 0777);
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

// void handle_user_redirections(t_com *command, e_tokenType rediflag, int *pipe_fd)
// {
//     int flags;
//     int fd;
// 	(void)pipe_fd;
//     if (!rediflag || !command || !command->operator)
//         return;

//     if (rediflag == RED_IN)
//     {
//         flags = O_RDONLY;
//     }
//     else if (rediflag == RED_OUT)
//     {
//         flags = O_WRONLY | O_CREAT | O_TRUNC;
//     }
//     else if (rediflag == APPEND)
//     {
//         flags = O_WRONLY | O_CREAT | O_APPEND;
//     }
//     else
//     {
//         // HERE_DOC - TODO later
//         return;
//     }

//     fd = open(command->operator->arg, flags, 0644);
//     if (fd == -1)
//     {
//         perror("open");
//         exit(EXIT_FAILURE);
//     }

//     if (dup2(fd, (rediflag == RED_IN) ? STDIN_FILENO : STDOUT_FILENO) == -1)
//     {
//         perror("dup2");
//         exit(EXIT_FAILURE);
//     }

//     close(fd);
// }

// void redirect_files(t_com *command, int *fd, int curr_cmd, int num_commands)
// {
// 	t_opp *curr_op = command->operator;
// 	// int flags, fd_redir = -1;

// 	if (curr_op && curr_op->operator)  //  redirections take precedence first
// 	{
// 		// loop over the fds
// 		while (curr_op)
// 		{
// 			handle_user_redirections(command, curr_op->operator, fd);
// 			curr_op = curr_op->next;
// 		}
// 	}
// 	else // handle redirections between pipes
// 	{
// 		// printf ("should not be called\n");
// 		if (curr_cmd < num_commands - 1)
// 			dup2(fd[1], STDOUT_FILENO);
// 		if (curr_cmd > 0)
// 			dup2(fd[0], STDIN_FILENO);
// 	}
// }
void redirect_files(t_com *command, int *pipe_fd, int curr_cmd, int num_commands)
{
	t_opp *curr_op = command->operator;

	if (curr_op && curr_op->operator) // User redirections take precedence
	{
		while (curr_op)
		{
			handle_user_redirections(command, curr_op->operator, pipe_fd);
			curr_op = curr_op->next;
		}
	}
	/*else // Handle redirections between pipes*/
	{
		if (curr_cmd < num_commands - 1 && pipe_fd[1] != -1)
		{
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			close(pipe_fd[1]); // Close after redirection
		}
		if (curr_cmd > 0 && pipe_fd[0] != -1)
		{
			if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			close(pipe_fd[0]); // Close after redirection
		}
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

int ft_execute_pipeline(char ***commands, int num_commands, int *return_value, t_data *data)
{
	int fds[MAX_FDS];
	int fd_count = 0;
	pid_t pid;
	int status;

	for (int i = 0; i < num_commands; i++)
	{
		int fd[2];
		if (i < num_commands - 1)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				close_all_fds(fds, fd_count);
				return 1;
			}
			fds[fd_count++] = fd[0];
			fds[fd_count++] = fd[1];
		}

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			close_all_fds(fds, fd_count);
			return 1;
		}
		else if (pid == 0)
		{
			// Child process
			// redirect_files(data->command, fd, i, num_commands);
			// redirect_files(data->command, (i > 0) ? &fds[fd_count - 2] : fd, i, num_commands);
			redirect_files(data->command, fd, i, num_commands);
			close_all_fds(fds, fd_count); // Close all unused fds in child
			execute_command(data, commands[i]);
			exit(EXIT_FAILURE); // In case execute_command fails
		}

		// Parent process
		if (i > 0)
		{
			close(fds[fd_count - 4]); // Close read end of previous pipe
			close(fds[fd_count - 3]); // Close write end of previous pipe
		}

		data->command = data->command->next;
	}

	close_all_fds(fds, fd_count);

	// Wait for all child processes
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			*return_value = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*return_value = 128 + WTERMSIG(status);
	}

	return 0;
}
