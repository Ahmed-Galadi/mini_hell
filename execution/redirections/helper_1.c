/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 04:54:38 by agaladi           #+#    #+#             */
/*   Updated: 2024/11/19 02:02:53 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_signal_received;

void	ftputstr_fd(int fd, char *s)
{
	if (!s || fd < 0)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

int	handle_red_helper(t_shell *data, t_opp **cur_op)
{
	if (g_signal_received)
		return (data->exit_status);
	if ((*cur_op)->operator == RED_OUT)
	{
		data->exit_status = setup_output_redirection((*cur_op)->arg, 0);
		if (data->exit_status)
		{
			return (data->exit_status);
		}
	}
	return (data->exit_status);
}

int	handle_redirection_loop(t_shell *data, t_opp *cur_op)
{
	while (cur_op)
	{
		if (cur_op->operator == RED_OUT && handle_red_helper(data, &cur_op))
			return (data->exit_status);
		else if (cur_op->operator == APPEND)
		{
			data->exit_status = setup_output_redirection(cur_op->arg, 1);
			if (data->exit_status)
				return (data->exit_status);
		}
		else if (cur_op->operator == RED_IN)
		{
			data->exit_status = setup_input_redirection(cur_op->arg, 0, data);
			if (data->exit_status)
				return (data->exit_status);
		}
		else if (cur_op->operator == HERE_DOC
			|| cur_op->operator == HERE_DOC_EXP)
			data->exit_status = setup_input_redirection(cur_op->arg, 1, data);
		cur_op = cur_op->next;
	}
	return (data->exit_status);
}

void	open_heredoc_helper(char **files, int *fd, int *count)
{
	*fd = open(files[*count], O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (*fd < 0)
		return (perror("open"));
	(*count)++;
}

void	heredoc_cleanup(int *fd, char *str)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
	if (str)
		free(str);
	rl_catch_signals = 0;
}
