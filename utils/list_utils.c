/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 05:39:53 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/02 18:46:48 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_lstback(t_opp *operators, t_opp *to_add)
{
	t_opp *current;

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
