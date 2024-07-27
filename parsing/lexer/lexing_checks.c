/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:17:28 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/27 19:52:45 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	trim_quotes(t_token **token)
{
	t_token	*current;
	char	*ptr_holder;
	
	current = *token;
	while (current)
	{
		if ((current->value)[0] == '\"')
		{
			current->type = D_QUOTE;
			ptr_holder = current->value;
			current->value = handle_quotes(ptr_holder);
			free(ptr_holder);
		}
		else if ((current->value)[0] == '\'')
		{
			current->type = S_QUOTE;
			ptr_holder = current->value;
			current->value = handle_quotes(ptr_holder);
			free(ptr_holder);
		}
		else
		{
			ptr_holder = current->value;
			current->value = handle_quotes(ptr_holder);
			free(ptr_holder);
		}
		current = current->next;
	}
}
