/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:51:20 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/26 16:51:19 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	check_env_creation(char **env)
{
	if (!env)
	{
		fprintf(stderr, "Failed to create environment array\n");
		exit(ERROR);
	}
}

static void	check_cmd_path(const char *path, char **args)
{
	if (!*args)
		exit (0);
	if (!path)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		exit(NOENT);
	}
}

static void	run_child_ps(int *count_hd, t_shell *data, char **args)
{
	t_com		*command;
	char		**env_array;
	const char	*cmd_path;

	command = data->command;
	if (*count_hd && !command->command[0])
	{
		handle_redirections(data);
		exit(0);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (handle_redirections(data))
		exit(ERROR);
	env_array = env_to_array(data->env);
	check_env_creation(env_array);
	cmd_path = get_path(args[0], data->env);
	data->last_exec_cmd = (char *)cmd_path;
	check_cmd_path(cmd_path, args);
	if (execve(cmd_path, args, env_array) == -1)
	{
		perror("Error execve");
		exit(PERM);
	}
}

int	ft_execute_external(char **args, t_shell *data, t_com *command)
{
	pid_t		pid;
	int			status;
	int			count;
	const char	*cmd_path;

	count = heredoc_count(command);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (perror("Fork Error"), 1);
	if (pid == 0)
		run_child_ps(&count, data, args);
	else
		if (waitpid(pid, &status, 0) == -1)
			return (perror("Waitpid Error"), 1);
	return (set_exit_status(&status));
}
