/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 05:22:37 by agaladi           #+#    #+#             */
/*   Updated: 2024/11/16 05:50:37 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cleanup_pipes(t_pipe *pipex)
{
	if (pipex->prev_pipe[0] != -1)
		close(pipex->prev_pipe[0]);
	if (pipex->prev_pipe[1] != -1)
		close(pipex->prev_pipe[1]);
	if (pipex->curr_pipe[0] != -1)
		close(pipex->curr_pipe[0]);
	if (pipex->curr_pipe[1] != -1)
		close(pipex->curr_pipe[1]);
}

void	killall(t_pipe *pipex)
{
	int	i;

	i = -1;
	cleanup_pipes(pipex);
	while (++i < pipex->curr_command)
	{
		if (pipex->pids[i] > 0)
		{
			kill(pipex->pids[i], SIGKILL);
			waitpid(pipex->pids[i], NULL, 0);
		}
	}
}
