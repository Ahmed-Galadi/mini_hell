/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:51:20 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/01 16:07:58 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_execute_external(char **args, t_shell *data, t_com *command)
{
	pid_t	pid;
	const char	*cmd_path;
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
		if (count && !command->command[0])
		{
			handle_redirections(data);
			exit(0);
		}
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (handle_redirections(data))
			exit(ERROR);
		char **env_array = env_to_array(data->env);
		if (!env_array)
		{
			fprintf(stderr, "Failed to create environment array\n");
			exit(ERROR);
		}
		cmd_path = get_path(args[0], data->env);
		if (!cmd_path)
		{
			fprintf(stderr, "Command not found: %s\n", args[0]);
			exit(NOENT);
		}
		if (execve(cmd_path, args, env_array) == -1)
		{
			perror("Error execve");
			exit(PERM);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			return (perror("Waitpid Error"), 1);
		if (WIFEXITED(status))
		{
			data->exit_status = WEXITSTATUS(status);
			if (data->exit_status == 2 && count)
				exit(2);
		}
		else if (WIFSIGNALED(status))
			data->exit_status = 128 + WTERMSIG(status);
	}
	return (data->exit_status);
}
