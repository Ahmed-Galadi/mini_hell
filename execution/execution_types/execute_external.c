/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:51:20 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/30 21:04:26 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_execute_external(char **args, t_shell *data, t_com *command)
{
	pid_t	pid;
	char	*cmd_path;
	int		status;
	int		count;
	
	count = heredoc_count(command);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork Error");
		return 1;
	}
	if (pid == 0)
	{
		// Child process
	if (count && !command->command[0])
	{
		handle_redirections(data);
		exit(0);
	}
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		handle_redirections(data);
		char **env_array = env_to_array(data->env);
		if (!env_array)
		{
			fprintf(stderr, "Failed to create environment array\n");
			exit(1);
		}
		cmd_path = find_command(args[0], env_array);
		if (!cmd_path)
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			exit(127);  // Exit with 127 for command not found
		}
		if (execve(cmd_path, args, env_array) == -1)
		{
			perror("Error execve");
			exit(126);  // Exit with 126 for execution error
		}
	}
	else
	{
		// Parent process
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Waitpid Error");
			return 1;
		}
		
		if (WIFEXITED(status))
		{
			data->exit_status = WEXITSTATUS(status);
			if (data->exit_status == 2)
				exit(2);
		}
		else if (WIFSIGNALED(status))
		{
			data->exit_status = 128 + WTERMSIG(status);
		}
	}
	return (data->exit_status);
}
