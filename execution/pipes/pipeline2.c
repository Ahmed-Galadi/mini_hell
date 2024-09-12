/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:25:49 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/12 15:07:15 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/wait.h>
#include <errno.h>

void	dup_fds(int	flag, int* fd, t_data* data)
{
	(void)fd;
	(void)data;
	int	i;
	int	fd_out;

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

const char* get_path(const char* cmd, t_env* env)
{
	int		i;
	char** executables;
	char* with_back_slash;
	char* full_path;
	t_env* curr;

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

void	redirections(t_opp* operator)
{
	t_opp* op;

	op = operator;
	if (!operator)
		return;
	while (op)
	{
		if (op->operator == RED_OUT)
		{
			int fd = open(op->arg, O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (op->operator == APPEND)
		{
			int fd = open(op->arg, O_CREAT | O_RDWR | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		op = op->next;
	}
}

int ft_execute_pipeline(char*** commands, int num_commands, int* return_value, t_data* data)
{
	int i, in, fd[2];
	pid_t pid;
	int status;
	(void)data;
	const char* full_path;

	in = STDIN_FILENO;
	i = 0;
	// replace this shit with data->command (linked list)
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return 1;
	}
	while (data->command)
	{
		pid = fork();
		if (pid == 0)
		{
			if (in != STDIN_FILENO)
			{
				dup2(in, STDIN_FILENO);
				close(in);
			}
			if (i < num_commands - 1)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}

			full_path = get_path(commands[i][0], data->env);
			if (full_path != NULL)
			{
				execve(full_path, commands[i], env_to_array(data->env));
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid < 0)
		{
			perror("fork");
			return 1;
		}
		i++;
		data->command = data->command->next;
	}


	close(fd[0]);
	close(fd[1]);


	while (wait(&status) > 0)
		;

	if (WIFEXITED(status))
		*return_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*return_value = 128 + WTERMSIG(status);

	return (0);
}