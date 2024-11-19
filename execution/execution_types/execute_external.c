/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:51:20 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/18 23:58:51 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_signal_received;

static void	run_child_ps(int *count_hd, t_shell *data, char **args)
{
	t_com		*command;

	command = data->command;
	if (*count_hd && !command->command[0])
	{
		handle_redirections(data);
		gc_free_all(LOCAL);
		if (g_signal_received)
			exit (1);
		exit(0);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (handle_redirections(data))
		(gc_free_all(LOCAL)), (exit(ERROR));
	execute_command(data, args);
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
