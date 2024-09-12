/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:25:49 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/12 15:27:35 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/wait.h>
#include <errno.h>

void dup_fds(int flag, int *fd, t_data *data)
{
	(void)fd;
	(void)data;
	int i;
	int fd_out;

	i = 0;
	printf("i %d flag %d\n", i, flag);
	printf("file %s\n", data->command->operator->arg);
	if (flag == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (flag)
	{
		fd_out = open(data->command->operator->arg, O_WRONLY | O_CREAT | O_TRUNC | 0777);
		if (fd_out)
		{
			dup2(fd_out, STDOUT_FILENO);
		}
	}
	close(fd[1]);
}

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
			int fd = open(op->arg, O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (op->operator== APPEND)
		{
			int fd = open(op->arg, O_CREAT | O_RDWR | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		op = op->next;
	}
}

void execute_command(t_data *data, char ***commands, int curr_cmd)
{
	const char *full_path;

	full_path = get_path(commands[curr_cmd][0], data->env);
	if (full_path != NULL)
	{
		execve(full_path, commands[curr_cmd], env_to_array(data->env));
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}

void	redirect_files(t_com *command, int *fd, int curr_cmd, int num_commands)
{
	int	std_in;
	int	std_out;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	if (curr_cmd == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else if ((curr_cmd % 2) == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	else if ((curr_cmd % 2) == 1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		
	}
	else if (curr_cmd == num_commands - 1)
	{
		
		dup2(STDOUT_FILENO, fd[1]);
	}
}

int ft_execute_pipeline(char ***commands, int num_commands, int *return_value, t_data *data)
{
	int i, fd[2];
	pid_t pid;
	int status;
	(void)num_commands;

	i = 0;
	while (data->command)
	{
		// create pipes
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
		if (pid == 0)
		{
			redirect_files(data, fd, i, num_commands);
			execute_command(data, commands, i);
			exit(EXIT_FAILURE); // In case execute_command fails
		}
		else
		{
			
	
		}
		i++;
		data->command = data->command->next;
	}

	close(fd[0]);
	close(fd[1]);

	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
		*return_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*return_value = 128 + WTERMSIG(status);
	return (0);
}