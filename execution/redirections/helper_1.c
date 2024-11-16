/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 04:54:38 by agaladi           #+#    #+#             */
/*   Updated: 2024/11/16 05:40:56 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	open_heredoc_helper(char **files, int *copy_stdin, int *fd, int *count)
{
	*copy_stdin = dup(STDIN_FILENO);
	*fd = open(files[*count], O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (*fd < 0)
		return (perror("open"));
	(*count)++;
}

//	trap_sigint: to not redirect output to files when signaled(ctrl-c).

int	handle_red_helper(t_shell *data, t_opp **cur_op)
{
	if (data->trap_sigint)
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

// norminette for void	open_heredoc(char**, t_opp*, int*, t_shell*)
void	heredoc_cleanup(int fd, int copy_stdin, char *str)
{
	close(fd);
	dup2(copy_stdin, STDIN_FILENO);
	close(copy_stdin);
	if (str)
		free(str);
}
