/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 05:39:53 by agaladi           #+#    #+#             */
/*   Updated: 2024/11/17 09:47:39 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_lstback(t_opp *operators, t_opp *to_add)
{
	t_opp	*current;

	current = operators;
	if (!operators)
		operators = to_add;
	else
	{
		while (current->next)
			current = current->next;
		current->next = to_add;
	}
}

t_token	*last_token(t_token *token)
{
	t_token	*current;

	current = token;
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

static int	has_spaces(t_opp *op)
{
	int	i;

	if (!op)
		return (-1);
	if (op->operator == RED_IN
		|| op->operator == RED_OUT
		|| op->operator == APPEND)
	{
		i = 0;
		while (op && op->arg && (op->arg)[i])
			if (ft_isspace((op->arg)[i++]))
				return (1);
	}
	return (0);
}

static void	should_remove_com(t_opp *current_op, t_com *current_com,
				int *should_remove)
{
	current_op = current_com->operator;
	while (current_op && !*should_remove)
	{
		if (has_spaces(current_op))
			*should_remove = 1;
		else if (has_spaces(current_op) == -1)
			return ;
		current_op = current_op->next;
	}
}

void	remove_abg_command(t_com **com)
{
	t_com	*prev_com;
	t_com	*current_com;
	t_opp	*current_op;
	int		should_remove;

	prev_com = NULL;
	current_com = *com;
	current_op = NULL;
	while (current_com)
	{
		should_remove = 0;
		should_remove_com(current_op, current_com, &should_remove);
		if (current_com->operator && should_remove)
		{
			if (prev_com)
				prev_com->next = current_com->next;
			else
				*com = current_com->next;
			current_com = current_com->next;
			continue ;
		}
		prev_com = current_com;
		current_com = current_com->next;
	}
}
