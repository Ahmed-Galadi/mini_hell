/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:25:49 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/12 17:04:57 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../minishell.h"
// #include <sys/wait.h>
// #include <errno.h>

// void dup_fds(int flag, int *fd, t_data *data)
// {
// 	(void)fd;
// 	(void)data;
// 	int i;
// 	int fd_out;

// 	i = 0;
// 	printf("i %d flag %d\n", i, flag);
// 	printf("file %s\n", data->command->operator->arg);
// 	if (flag == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 	}
// 	if (flag)
// 	{
// 		fd_out = open(data->command->operator->arg, O_WRONLY | O_CREAT | O_TRUNC | 0777);
// 		if (fd_out)
// 		{
// 			dup2(fd_out, STDOUT_FILENO);
// 		}
// 	}
// 	close(fd[1]);
// }

// const char *get_path(const char *cmd, t_env *env)
// {
// 	int i;
// 	char **executables;
// 	char *with_back_slash;
// 	char *full_path;
// 	t_env *curr;

// 	executables = NULL;
// 	if (!cmd || !env)
// 		return (NULL);
// 	curr = env;
// 	while (curr->next)
// 	{
// 		if (ft_strncmp(curr->key, "PATH", 4) == 0)
// 		{
// 			executables = ft_split(curr->value, ':');
// 			break;
// 		}
// 		curr = curr->next;
// 	}
// 	i = 0;
// 	while (executables[i])
// 	{
// 		with_back_slash = ft_strjoin(executables[i], "/");
// 		full_path = ft_strjoin(with_back_slash, cmd);
// 		if (access(full_path, F_OK | X_OK) == 0)
// 			return (full_path);
// 		i++;
// 	}
// 	return (NULL);
// }

// void redirections(t_opp *operator)
// {
// 	t_opp *op;

// 	op = operator;
// 	if (!operator)
// 		return;
// 	while (op)
// 	{
// 		if (op->operator== RED_OUT)
// 		{
// 			int fd = open(op->arg, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		if (op->operator== APPEND)
// 		{
// 			int fd = open(op->arg, O_CREAT | O_RDWR | O_APPEND, 0644);
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 		}
// 		op = op->next;
// 	}
// }

// void execute_command(t_data *data, char ***commands, int curr_cmd)
// {
// 	const char *full_path;

// 	full_path = get_path(commands[curr_cmd][0], data->env);
// 	if (full_path != NULL)
// 	{
// 		execve(full_path, commands[curr_cmd], env_to_array(data->env));
// 		perror("execvp");
// 		exit(EXIT_FAILURE);
// 	}
// }

// int ft_execute_pipeline(char ***commands, int num_commands, int *return_value, t_data *data)
// {
// 	int i, std_in, fd[2];
// 	pid_t pid;
// 	int status;
// 	(void)num_commands;

// 	i = 0;
// 	std_in = dup(STDIN_FILENO);
// 	while (data->command)
// 	{
// 		if (i != num_commands - 1)
// 		{
// 			if (pipe(fd) == -1)
// 			{
// 				perror("pipe");
// 				return 1;
// 			}
// 		}
// 		pid = fork();
// 		if (pid < 0)
// 			return (perror("fork"), 1);
// 		if (pid == 0)
// 		{
// 			// Input redirection
// 			if (i > 0)
// 			{
// 				dup2(std_in, STDIN_FILENO);
// 				close(std_in);
// 			}

// 			// Output redirection
// 			int output_fd = STDOUT_FILENO;
// 			if (data->command->operator&& data->command->operator->operator== RED_OUT)
// 			{
// 				int fd_out = open(data->command->operator->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 				if (fd_out == -1)
// 				{
// 					perror("open");
// 					exit(EXIT_FAILURE);
// 				}
// 				output_fd = fd_out;
// 			}

// 			// Pipe output (only if not redirecting to a file)
// 			if (i < num_commands - 1 && output_fd == STDOUT_FILENO)
// 			{
// 				close(fd[0]);
// 				output_fd = fd[1];
// 			}

// 			// Perform the final output redirection
// 			if (output_fd != STDOUT_FILENO)
// 			{
// 				dup2(output_fd, STDOUT_FILENO);
// 				close(output_fd);
// 			}

// 			execute_command(data, commands, i);
// 			exit(EXIT_FAILURE); // In case execute_command fails
// 		}
// 		else
// 		{
// 			if (i > 0)
// 				close(std_in);
// 			if (i < num_commands - 1)
// 			{
// 				close(fd[1]);
// 				std_in = fd[0];
// 			}
// 		}
// 		i++;
// 		data->command = data->command->next;
// 	}

// 	close(fd[0]);
// 	close(fd[1]);

// 	while (wait(NULL) > 0)
// 		;
// 	if (WIFEXITED(status))
// 		*return_value = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 		*return_value = 128 + WTERMSIG(status);
// 	return (0);
// }

#include "../../minishell.h"
#include <sys/wait.h>
#include <errno.h>
#define MAX_FDS 1024  // Adjust this based on your system's limits

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
        execve(full_path, commands, env_to_array(data->env));
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(stderr, "Command not found: %s\n", commands[0]);
        exit(EXIT_FAILURE);
    }
}

void redirect_files(t_com *command, int *fd, int curr_cmd, int num_commands)
{
    if (curr_cmd == 0)
    {
        // First command: only redirect stdout
        if (!command->operator)
              dup2(fd[1], STDOUT_FILENO);
        else
            redirections(command->operator);
    }
    else if (curr_cmd == num_commands - 1)
    {
        // Last command: only redirect stdin
        if (!command->operator)
               dup2(fd[0], STDIN_FILENO);
        else
            redirections(command->operator);
    }
    else
    {
        // Middle commands: redirect both stdin and stdout
        if (!command->operator)
        {
            dup2(fd[0], STDIN_FILENO);
            dup2(fd[1], STDOUT_FILENO);
        }
        else
            redirections(command->operator);
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
            redirect_files(data->command, fd, i, num_commands);
            close_all_fds(fds, fd_count);  // Close all unused fds in child
            execute_command(data, commands[i]);
            exit(EXIT_FAILURE);  // In case execute_command fails
        }

        // Parent process
        if (i > 0)
        {
            close(fds[fd_count - 4]);  // Close read end of previous pipe
            close(fds[fd_count - 3]);  // Close write end of previous pipe
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