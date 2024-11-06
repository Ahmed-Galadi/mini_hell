/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:51:20 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/06 07:47:19 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_signal_received;

static void	check_env_creation(char **env)
{
	if (!env)
	{
		ft_printf(2, "Failed to create environment array\n");
		gc_free_all(LOCAL);
		exit(ERROR);
	}
}

static void	check_cmd_path(const char *path, char **args)
{
	if (!*args)
		exit (0);
	if (!path)
	{
		ft_printf(2, "%s: command not found\n", args[0]);
		gc_free_all(LOCAL);
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
		gc_free_all(LOCAL);
		exit(0);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (handle_redirections(data))
		(gc_free_all(LOCAL)), (exit(ERROR));
	if (g_signal_received)
		(gc_free_all(LOCAL)), (exit(1));
	env_array = env_to_array(data->env);
	check_env_creation(env_array);
	cmd_path = get_path(args[0], data->env);
	check_cmd_path(cmd_path, args);
	execve(cmd_path, args, env_array);
	((perror("Error")), (gc_free_all(LOCAL)), (exit(PERM)));
}

int	ft_execute_external(char **args, t_shell *data, t_com *command)
{
	pid_t		pid;
	int			status;
	int			count;

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
