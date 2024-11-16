/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:08:48 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/16 20:31:33 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	valid_operator(t_tokenType operator_type, int *flags, int *default_fd)
{
	if (operator_type == RED_IN)
	{
		*default_fd = STDIN_FILENO;
		*flags = O_RDONLY;
	}
	else if (operator_type == RED_OUT)
	{
		*default_fd = STDOUT_FILENO;
		*flags = O_RDWR | O_CREAT | O_TRUNC;
	}
	else if (operator_type == APPEND)
	{
		*default_fd = STDOUT_FILENO;
		*flags = O_RDWR | O_CREAT | O_APPEND;
	}
	else if (operator_type == HERE_DOC || operator_type == HERE_DOC_EXP)
		return (1);
	else
		return (0);
	return (1);
}

int	is_redirection_out(t_tokenType operator, char *file)
{
	if (operator == RED_OUT || operator == APPEND)
	{
		if (!ft_strcmp(file, "/dev/stdout"))
			return (0);
		return (1);
	}
	return (0);
}

int	is_redirection_in(t_tokenType operator)
{
	if (operator == RED_IN || operator == HERE_DOC || operator == HERE_DOC_EXP)
		return (1);
	return (0);
}

int	count_docs(t_opp *op)
{
	int	count;

	count = 0;
	while (op)
	{
		if (op->operator == HERE_DOC || op->operator == HERE_DOC_EXP)
			count++;
		op = op->next;
	}
	return (count);
}

int	heredoc_count(t_com *command)
{
	int		count;
	t_com	*curr;
	t_opp	*op;

	curr = command;
	count = 0;
	while (curr)
	{
		op = curr->operator;
		count += count_docs(curr->operator);
		curr = curr->next;
	}
	return (count);
}
