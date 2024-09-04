/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:25:49 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/04 15:15:31 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/wait.h>
#include <errno.h>

const char *get_path(const char *cmd, t_env *env)
{
	int		i;
	char	**executables;
	char	*with_back_slash;
	char	*full_path;
	t_env	*curr;

	executables = NULL;
	if (!cmd || !env)
		return (NULL);
	curr = env;
	while (curr->next)
	{
		if (ft_strncmp(curr->key, "PATH", 4) == 0)
		{
			executables = ft_split(curr->value, ':');
			break ;
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

int ft_execute_pipeline(char ***commands, int num_commands, int *return_value, t_data *data)
{
	int i, in, fd[2];
	pid_t pid;
	int status;
	(void)data;
	const char	*full_path;

	in = STDIN_FILENO;
	for (i = 0; i < num_commands; i++)
	{
		if (i < num_commands - 1)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				return 1;
			}
		}
		pid = fork();
		if (pid == 0)
		{
			// Child process
			if (in != STDIN_FILENO)
			{
				dup2(in, STDIN_FILENO);
				close(in);
			}
			if (i < num_commands - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
			}
			close(fd[1]);
			full_path = get_path(commands[i][0], data->env);
			//execvp(commands[i][0], commands[i]);
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

		// Parent process
		if (in != STDIN_FILENO)
			close(in);
		if (i < num_commands - 1)
		{
			close(fd[1]);
			in = fd[0];
		}
	}

	// Wait for all children
	while (wait(&status) > 0)
		;

	if (WIFEXITED(status))
		*return_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*return_value = 128 + WTERMSIG(status);

	return (0);
}